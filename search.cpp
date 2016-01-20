#include <iostream>
#include <set>
#include <vector>
#include <cctype>
#include <string>
#include <QApplication>
#include <fstream>
#include <map>
#include "searcheng.h"
#include "mdparser.h"
#include "searchUI.h"

int main(int argc, char* argv[]){
    //Find config
    std::string config = "";
    if(argc < 2)
        config = "config.txt";
    else
        config = argv[1];

    //Check config
    std::ifstream in_file(config.c_str());
    if(in_file.fail()){
        std::cerr<<"ERROR: Invalid configuration file."<<std::endl;
        in_file.close();
        return 1;
    }

    //Read config
    std::map<std::string, std::string> map_par_val;
    std::string line;
    while(getline(in_file,line)){
        if(line=="")
            continue;
        else{
        	for(unsigned int i=0;i<line.size();i++){
            	if(isspace(line[i])){
            		if(i == line.size()-1){
            			line = line.substr(0,i);
            		}
            		else{
            			line = line.substr(0,i)+line.substr(i+1);
            		}
            		i--;
            	}
        	}
        }
        bool eqSign = false;
        std::string parameter = "";
        std::string value = "";
        for(int i=0;(unsigned)i<line.size();i++){
            if(!eqSign && line[i]=='#'){
                break;
            }            
            else if(!eqSign && line[i]=='='){
            	parameter = line.substr(0,i);
            	if(map_par_val.count(parameter)!=0){
		    		std::cerr<<"Warning: more than one "<<parameter<<" detected, duplicates ignored.";
		    		break;
            	}
            	line=line.substr(i+1);
            	i=-1;
            	eqSign = true;
            }
            else if(eqSign){
            	if(line[i]=='#'){
            		value = line.substr(0,i);
            		map_par_val.insert(make_pair(parameter,value));
            		break;
            	}
            	else if((unsigned)i==line.size()-1){
            		value = line.substr(0,i+1);
            		map_par_val.insert(make_pair(parameter,value));
            		break;
            	}		    	
            }
        }
    }    

    //Check for necessary files
    if(map_par_val.count("INDEX_FILE")==0){
    	std::cerr<<"ERROR: Missing INDEX_FILE"<<std::endl;
    	return 1;
    }
    if(map_par_val.count("RESTART_PROBABILITY")==0){
    	std::cerr<<"ERROR: Missing RESTART_PROBABILITY"<<std::endl;
    	return 1;
    }
    if(map_par_val.count("STEP_NUMBER")==0){
    	std::cerr<<"ERROR: Missing STEP_NUMBER"<<std::endl;
    	return 1;
    }

    //Parse the index file
    SearchEng sn;
    PageParser* parser = new MDParser;
    sn.add_parse_from_index_file(map_par_val["INDEX_FILE"] ,parser);
    delete parser;

    QApplication app(argc, argv);
    SearchUI mainWindow;
    //Pass data into Qt
    mainWindow.set_searchEngine(sn);
    mainWindow.set_restart_probability( atof(map_par_val["RESTART_PROBABILITY"].c_str()) );
    mainWindow.set_step( atoi(map_par_val["STEP_NUMBER"].c_str()) );
    mainWindow.show();
    return app.exec();
}

//Compile without using the makefile: g++ -g -Wall search.cpp searcheng.cpp MDParser.cpp myset.cpp webpage.cpp -o search