#include <fstream>
#include <vector>
#include <iostream>
#include <exception>
#include <map>

bool unexplored(std::string link, std::vector<std::string>& explored){
	for(unsigned int i=0;i<explored.size();i++){
		if(link==explored[i])
			return false;
	}
	return true;
}

std::vector<std::string> getLinks(std::string filename, std::vector<std::string>& explored){
	std::vector<std::string> result;
	std::ifstream input_file(filename.c_str());
	if(input_file.fail()){
		input_file.close();
		throw std::exception();
	}

	std::string input="";
	std::string input_it="";
	bool input_valid=getline(input_file, input);
	if(input_valid){
		while(getline(input_file, input_it))
			input=input+"\n"+input_it;
		for(unsigned int i=0;i<input.size();i++){
			if(isalpha(input[i]))
				input[i]=tolower(input[i]);
		}	
	}

	if(input.size()<4){
		input_file.close();
		return result;
	}

	bool isLink=false;
	bool getLink=false;
	for(unsigned int i = 0;i < input.size();i++){
		if(input[i] == '[' && getLink == false){
			i++;
			int temp = i;
			unsigned int closedBracket=0;
			std::string checker="";
			while(i<input.size()){
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
			if(i+1<input.size()){
				input = input.substr(i);
				i=-1;
			}

		}
		else if(input[i] == ']' && isLink == true && getLink == false){
			input=input.substr(i+2);
			isLink=false;
			getLink=true;
			i=-1;

		}
		else if(input[i] == ')'&& getLink==true){
			std::string temp = input.substr(0,i);
			if(unexplored(temp, explored))
				result.push_back(temp);
			getLink=false;
			if(i+1<input.size()){
				input=input.substr(i+1);
				i=-1;
			}

		}
	}
	input_file.close();
	return result;
}




void crawl(std::string index_filename, std::string output_filename, std::vector<std::string>& explored){
	std::vector<std::string> results;
	try{
		//getLinks has a built in function to check for repeats as it parses.
		 results = getLinks(index_filename, explored);
	}
	//The file doesn't exist.
	catch (std::exception& e){
		return;
	}

	//The file exists, add it to index
	std::ofstream output_file(output_filename.c_str(), std::ios_base::app);
	if(output_file.fail()){
		output_file.close();
		std::cerr<<"The output file <"<<output_filename<<"> does not exist!"<<" Could not be parsed by crawler"<<std::endl;
		return;
	}
	//Check for repeats
	if(unexplored(index_filename, explored)){
		output_file<<index_filename<<std::endl;
		explored.push_back(index_filename);
	}
 	output_file.close();

 	//The file has no outgoing links, no need for recursion.
	if(results.size()==0){
		return;
	}

	//Visit the outgoing links
	for(unsigned int i=0;i<results.size();i++){
		//Check for repeats
		if(unexplored(results[i], explored)){
			crawl(results[i],output_filename, explored);
		}
	}


	//Make sure if we can't open the file there is a different return value than if the link simply doesn't contain any outgoing links.
}

void crawl_starter(std::string index_filename, std::string output_filename, std::vector<std::string>& explored){
	std::ifstream in_file(index_filename.c_str());
	if(in_file.fail()){
		std::cerr<<"ERROR: The index file <"<<index_filename<<"> does not exist!"<<" Could not be parsed by crawler.cpp"<<std::endl;
		in_file.close();
		return;
	}

	std::string fn;
	while(getline(in_file,fn)){
		//Check for empty lines
		if(fn=="")
			continue;
		crawl(fn,output_filename,explored);
	}
	in_file.close();
}

int main(int argc, char* argv[]){
    //Find config
    std::string config = "";
    if(argc < 2)
        config = "config_crawler.txt";
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
        	for(int i=0;(unsigned)i<line.size();i++){
            	if(isspace(line[i])){
            		if((unsigned)i == line.size()-1){
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
		    		std::cerr<<"Warning: more than one "<<parameter<<" detected, duplicates ignored."<<std::endl;
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
    if(map_par_val.count("OUTPUT_FILE")==0){
    	std::cerr<<"ERROR: Missing OUTPUT_FILE"<<std::endl;
    	return 1;
    }

    //Clear output file
    std::ofstream file(map_par_val["OUTPUT_FILE"].c_str());
    if(file.fail()){
        std::cout<<"ERROR: Invalid output file: "<<map_par_val["OUTPUT_FILE"]<<std::endl;
        return 1;
    }
    file.close( );

    //Create index file
    std::vector<std::string> explored;
    crawl_starter(map_par_val["INDEX_FILE"], map_par_val["OUTPUT_FILE"], explored);
        
	return 0;
}
//g++ -g -Wall main.cpp mdparser.cpp webpage.cpp -o main