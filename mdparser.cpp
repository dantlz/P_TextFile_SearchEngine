#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
#include <exception>
#include "mdparser.h"

MDParser::MDParser(){}
MDParser::MDParser(std::string index_filename){
	std::ifstream index(index_filename.c_str());
	if(index.fail()){
		std::cerr<<"Index file "<<index_filename<<" could not be opened by MDParser!"<<std::endl;
		throw std::exception();
	}
	std::string fn;
	while(getline(index,fn)){
		//Check for empty lines
		if(fn=="")
			continue;
		validLinks.insert(fn);
		
	}
	
}
MDParser::~MDParser() {}

//Parses a file and returns all unique words according to some parser rules and all hyperlinks based on the format the parser is designed to implement
void MDParser::parse(std::string filename, myset<std::string>& allWords,myset<std::string>& allLinks){

	//Preparation
	std::ifstream in_file(filename.c_str());
	if(in_file.fail()){
		std::cerr<<"The file <"<<filename<<"> does not exist!"<<" Could not be parsed by MDParser"<<std::endl;
		in_file.close();
		return;
	}
	std::string input="";
	std::string input2="";
	bool firstLine=getline(in_file, input);
	if(firstLine){
		while(getline(in_file, input2))
			input=input+"\n"+input2;
		input = lowerCase( input );
	}
	//Parsing
	bool isLink=false;
	bool getLink=false;
	for( int i = 0;(unsigned)i < input.size();i++){
		if(input[i] == '[' && getLink == false){
			i++;
			int temp = i;
			int closedBracket=0;
			std::string checker="";
			while((unsigned)i<input.size()){
				if(input[i] == ']'){
					checker = checker + input[i];
					closedBracket=i;
				}
				else if(input[i] == '('){
					if(i==closedBracket+1)
					checker = checker + input[i];
				}
				else if(input[i] == ')'){
					checker = checker + input[i];
					if(checker=="]()")
						break;
				}
				i++;
			}
			i = temp;
			if(checker.size() >=3 && (checker.substr(0,3) == "]()") ){
				isLink=true;
			}			
			std::string result = input.substr(0,i-1);
			if(result!="")
				allWords.insert(result);
			if((unsigned)i+1<input.size()){
				input = input.substr(i);
				i=-1;
			}

		}
		else if(input[i] == ']' && isLink == true && getLink == false){
			std::string result = input.substr(0,i);
			if(result!="")
				allWords.insert(result);
			input=input.substr(i+2);
			isLink=false;
			getLink=true;
			i=-1;

		}
		else if(input[i] == ')'&& getLink==true){
			std::string link = input.substr(0,i);
			//Check if the link is valid. 
			std::ifstream temp(link.c_str());
			if(!temp.fail())
				allLinks.insert(link);
			temp.close();
			getLink=false;
			if((unsigned)i+1<input.size()){
				input=input.substr(i+1);
				i=-1;
			}

		}
		else if(  input[i]=='\0' || (!isalpha(input[i]) && !isdigit(input[i]) && getLink == false)){
			std::string result = input.substr(0,i);
			if(result!="")
				allWords.insert(result);
			if((unsigned)i+1<input.size()){
				input=input.substr(i+1);
				i=-1;
			}
		}
	}

	if(input!=""&&input!=" "){
		allWords.insert(input);
	}
}

//Function for converting all alphabets to lower case
std::string MDParser::lowerCase(std::string s){
	unsigned int i=0;
	while (i<s.size()){
		if(isalpha(s[i]))
			s[i]=tolower(s[i]);
		i++;
	}
	return s;
}