#ifndef SEARCHENG_H
#define SEARCHENG_H
#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
	public:
	SearchEng();
	~SearchEng();
	void add_parse_from_index_file(std::string index_file,PageParser* parser);
	void add_parse_page(std::string filename,PageParser* parser);
	myset<WebPage*> findWord(std::string word);

 	private:
 	std::map<std::string, WebPage*> map_filename_WebPages;
 	std::map<std::string, myset<WebPage*> > map_Words_MySetWebPage; 
 	std::string index_filename;
};

#endif
