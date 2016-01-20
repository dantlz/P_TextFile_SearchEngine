#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "searcheng.h"
#include "mdparser.h"

SearchEng::SearchEng(){}

SearchEng::~SearchEng(){
	std::map<std::string, WebPage*>::iterator it;
	for(it=map_filename_WebPages.begin();it!=map_filename_WebPages.end();++it){
		delete it->second;
	}
}

void SearchEng::add_parse_from_index_file(std::string index_file, PageParser* parser){
	index_filename = index_file;
	std::ifstream in_file(index_file.c_str());
	if(in_file.fail()){
		std::cerr<<"The index file <"<<index_file<<"> does not exist!"<<" Could not be parsed by searcheng.cpp"<<std::endl;
		in_file.close();
		return;
	}

	std::string fn;
	while(getline(in_file,fn)){
		//Check for empty lines
		if(fn=="")
			continue;
		//Even though all links in index are supposed to be valid, because crawler ensures only valid links
		//are added to its output, the index file, we will still check for invalid links here just to
		//be extra safe.
		std::ifstream temp(fn.c_str());
		if(!temp.fail()){
			map_filename_WebPages[fn]=new WebPage(fn);
		}
		temp.close();
	}

	std::map<std::string, WebPage*>::iterator it;
	for(it = map_filename_WebPages.begin();it!=map_filename_WebPages.end();++it){
		add_parse_page(it->first,parser);
	}
}

void SearchEng::add_parse_page(std::string filename, PageParser* parser){
	//Variables and holders
	WebPage* currentPage = map_filename_WebPages[filename];
	myset<std::string> allWords ;
	myset<std::string> outLinks ;
	parser = new MDParser(index_filename);
	parser->parse(filename,allWords,outLinks);
	delete parser;

	currentPage->all_words(allWords);
	typename myset<std::string>::iterator it;	
	for(it = outLinks.begin(); it != outLinks.end(); ++it){
		//Check here to see if it contains any none existent links
		//If there is, add it in. There is no possibility for a link in outLinks to be invalid
		//because when we used MDparser to parse links into outLinks, only valid links were 
		//added in.
		if(map_filename_WebPages.count(*it)==0){
			map_filename_WebPages[*it]=new WebPage(*it);
		}
		currentPage->add_outgoing_link(map_filename_WebPages[*it]);
		WebPage* a = map_filename_WebPages[*it];
		a->add_incoming_link(currentPage);
	}

	//At this point, each filename from index has been made into a webpage with a filename, all unique words, all incoming links, and all outgoing links.
	//All of these webpages are stored in the map map_filename_WebPages with its filename as a keyword and the webpage itself as a value.  

	//Populate the word to a set of webpages map.
	typename myset<std::string>::iterator it2;
	for(it2 = allWords.begin(); it2!=allWords.end(); ++it2){
		std::string currentWord = *it2;
		if(map_Words_MySetWebPage.count(currentWord) != 0){
			map_Words_MySetWebPage[currentWord].insert(currentPage);
		}
		else{
			myset<WebPage*> newSet;
			newSet.insert(currentPage);
			map_Words_MySetWebPage[currentWord] =  newSet;
		}
		
	}
}

//Function to retrieve a set of all webpages that contain a certain word
myset<WebPage*> SearchEng::findWord(std::string word){
	//If the word isn't in any webpages
	if(map_Words_MySetWebPage.count(word)==0){
		myset<WebPage*> notFound;
		return notFound;
	}
	else{
		myset<WebPage*> result = map_Words_MySetWebPage[word];
		for(myset<WebPage*>::iterator it = map_Words_MySetWebPage[word].begin();it!=map_Words_MySetWebPage[word].end();it++){
			result = result.set_union((*it)->incoming_links());
			result = result.set_union((*it)->outgoing_links());
		}
		return result;
	}
}
