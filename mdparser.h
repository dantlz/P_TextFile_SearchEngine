#ifndef MDPARSER_H
#define MDPARSER_H
#include <string>
#include "myset.h"
#include "pageparser.h"

class MDParser: public PageParser {
public:
	MDParser();
	MDParser(std::string);
	~MDParser();

	//Parses a file and returns all unique words according to some parser rules and all hyperlinks based on the format the parser is designed to implement
	void parse(std::string filename, myset<std::string>& allWords, myset<std::string>& allLinks);

	std::string lowerCase(std::string s);
private:
	myset<std::string> validLinks;
};

#endif
