#include <QListWidgetItem>
#include <QSize>
#include <sstream>
#include <iostream>
#include "searchUI.h"
#include "myset.h"
#include "mdparser.h"
#include "listitem.h"
#include "mainlistitem.h"
#include "msort.h"







//___________________PUBLIC FUNCTIONS____________________

SearchUI::SearchUI() : QWidget(NULL){
    //std::set up the interface
    main_layout = new QGridLayout;
    quitButton = new QPushButton("Quit");        
    searchInput = new QLineEdit;
    searchButton = new QPushButton("Search");
    radio_single = new QRadioButton("Single");
    radio_and = new QRadioButton("AND");
    radio_or = new QRadioButton("OR");   
    searchType_group = new QGroupBox;
    searchType_layout = new QHBoxLayout; 
    mainList_pageRank_button = new QRadioButton("Page Rank");
    mainList_nameSort_button = new QRadioButton("Filename");
    mainList_inLink_button = new QRadioButton("Incoming Links");
    mainList_outLink_button = new QRadioButton("Outgoing Links");
    mainListSort_group = new QGroupBox;
    mainListSort_layout = new QHBoxLayout;
	mainList_sortType = new QButtonGroup;
    mainList = new QListWidget;

    radio_single->setChecked(true);
    mainList_pageRank_button->setChecked(true);
    searchInput->setPlaceholderText("Enter search word(s) here");
    main_layout->addWidget(quitButton,0,0,1,1);
    main_layout->addWidget(searchInput, 1,0,1,2);
    main_layout->addWidget(searchButton,1,2,1,1);
    searchType_layout->addWidget(radio_single);
    searchType_layout->addWidget(radio_and);
    searchType_layout->addWidget(radio_or);
    searchType_group->setLayout(searchType_layout);
    searchType_group->setTitle("Search Type");
    main_layout ->addWidget(searchType_group,2,0,1,3);
    mainListSort_layout->addWidget(mainList_pageRank_button);
    mainListSort_layout->addWidget(mainList_nameSort_button);
    mainListSort_layout->addWidget(mainList_inLink_button);
    mainListSort_layout->addWidget(mainList_outLink_button);
    mainListSort_group->setLayout(mainListSort_layout);
    mainListSort_group->setTitle("Sort Results");
    main_layout->addWidget(mainListSort_group,4,0,1,4);
    mainList_sortType->addButton(mainList_nameSort_button);
    mainList_sortType->addButton(mainList_inLink_button);
    mainList_sortType->addButton(mainList_outLink_button);
    mainList_sortType->addButton(mainList_pageRank_button);
    main_layout->addWidget(mainList, 6,0,8,4);
    setLayout(main_layout);

    details_window = new QWidget;
    details_layout = new QGridLayout;
    currentFile_name = new QLabel("Current FIle:");
    nameDisplay = new QLabel;
    closeButton = new QPushButton("Close");
    webContent = new QTextEdit;
    inList_sortType = new QButtonGroup;
    inListSort_group = new QGroupBox;
    inListSort_layout = new QHBoxLayout;
    inList_nameSort_button = new QRadioButton("Filename");
    inList_inLink_button = new QRadioButton("Incoming Links");
    inList_outLink_button = new QRadioButton("Outgoing Links");
    inList = new QListWidget; 
    outList_sortType = new QButtonGroup;
    outListSort_group = new QGroupBox;
    outListSort_layout = new QHBoxLayout;
    outList_nameSort_button = new QRadioButton("Filename");
    outList_inLink_button = new QRadioButton("Incoming Links");
    outList_outLink_button = new QRadioButton("Outgoing Links");
    outList = new QListWidget;

    inList_nameSort_button->setChecked(true);
    outList_nameSort_button->setChecked(true);
    details_window->setLayout(details_layout);
    details_layout->addWidget(currentFile_name,0,0,1,1);
    details_layout->addWidget(nameDisplay,0,1,1,2);
    details_layout->addWidget(closeButton,0,2,1,1);
    details_layout->addWidget(webContent,1,0,4,4);
    webContent->setReadOnly(true);
    inListSort_layout->addWidget(inList_nameSort_button);
	inListSort_layout->addWidget(inList_inLink_button);
	inListSort_layout->addWidget(inList_outLink_button);    
	inListSort_group->setLayout(inListSort_layout);
	inListSort_group->setTitle("Incoming Links - Sorted By:");
	details_layout->addWidget(inListSort_group,5,0,1,3);
    inList_sortType->addButton(inList_nameSort_button);
    inList_sortType->addButton(inList_inLink_button);
    inList_sortType->addButton(inList_outLink_button);
    details_layout->addWidget(inList,7,0,4,4);        
    outListSort_layout->addWidget(outList_nameSort_button);
    outListSort_layout->addWidget(outList_inLink_button);
    outListSort_layout->addWidget(outList_outLink_button);
    outListSort_group->setLayout(outListSort_layout);
    outListSort_group->setTitle("Outgoing Links - Sorted By:");
    details_layout->addWidget(outListSort_group,11,0,1,3);
    outList_sortType->addButton(outList_nameSort_button);
    outList_sortType->addButton(outList_inLink_button);
    outList_sortType->addButton(outList_outLink_button);
    details_layout->addWidget(outList,13,0,4,4);

    //Standardize the display column size
    for(int i=0;i<10;i++){
        main_layout->setColumnStretch(i,1);
        details_layout->setColumnStretch(i,1);
    }

    //Connections
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(quitButton_clicked()));

    QObject::connect(searchInput, SIGNAL(returnPressed()), this, SLOT(returnKey_hit()));
    QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(searchButton_clicked()));

    QObject::connect(mainList_sortType, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(mainList_sortType_clicked()));
    QObject::connect(mainList, SIGNAL(currentRowChanged(int)), this, SLOT(mainList_item_clicked(int)));

    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(closeButton_clicked()));

    QObject::connect(inList, SIGNAL(currentRowChanged(int)), this, SLOT(inList_item_clicked(int)));
    QObject::connect(inList_sortType, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(inList_sortType_clicked()));

    QObject::connect(outList, SIGNAL(currentRowChanged(int)), this, SLOT(outList_item_clicked(int)));  
    QObject::connect(outList_sortType, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(outList_sortType_clicked()));  

}
SearchUI::~SearchUI(){

	//delete everything in the lists
    for( int i=0;i<mainList->count();i++){
    	delete mainList->itemWidget(mainList->item(i));
    }
    for( int i=0;i<inList->count();i++){
    	delete inList->itemWidget(inList->item(i));
    }
    for( int i=0;i<outList->count();i++){
    	delete outList->itemWidget(outList->item(i));
    }
    mainList->clear();
    inList->clear();
    outList->clear();

    //delete everything in the vectors and sets
    for(unsigned int i=0;i<mainList_data.size();i++){
    	delete mainList_data[i];
    }
    for(unsigned int i=0;i<inList_data.size();i++){
    	delete inList_data[i];
    }
    for(unsigned int i=0;i<outList_data.size();i++){
    	delete outList_data[i];
    }
    for(std::set<WebPage*>::iterator it = search_result.begin(); it != search_result.end(); ++it){
    	delete *it;
    }
    mainList_data.clear();
    inList_data.clear();
    outList_data.clear();
    search_result.clear();

    //Delete all Qt items
    delete inList_nameSort_button;
    delete inList_inLink_button;
    delete inList_outLink_button;
    delete inList;
    delete outList_nameSort_button;
    delete outList_inLink_button;
    delete outList_outLink_button;
    delete outList;
    delete currentFile_name;
    delete nameDisplay;
    delete closeButton;
    delete webContent;
    delete inList_sortType;
    delete inListSort_group;
    delete inListSort_layout;
    delete outList_sortType;
    delete outListSort_group;
    delete outListSort_layout;
    delete details_window;
   	delete details_layout;

    delete mainList;
    delete mainList_pageRank_button;
    delete mainList_nameSort_button;
    delete mainList_inLink_button;
    delete mainList_outLink_button;
    delete radio_single;
    delete radio_and;
    delete radio_or; 
    delete quitButton;        
    delete searchInput;
    delete searchButton;
    delete searchType_group;
    delete searchType_layout; 
    delete mainListSort_group;
   	delete mainListSort_layout;
	delete mainList_sortType;
    delete main_layout;
}
//std::set the search engine
void SearchUI::set_searchEngine(SearchEng& search_eng){
        sn=search_eng;
}
//std::set the search engine
void SearchUI::set_restart_probability(double rp){
        restart_probability=rp;
}
//std::set the search engine
void SearchUI::set_step(int step){
        step_number=step;
}


















//__________________________SLOTS____________________________
//The user clicked the quit button
void SearchUI::quitButton_clicked(){
    exit(0);
}
//The user hit the return key in the search input
void SearchUI::returnKey_hit(){
    searchButton_clicked();
}
//The user hit the search button
void SearchUI::searchButton_clicked(){

    std::string input = (searchInput->text()).toStdString();

    if(input ==""){
        return;
    }
    else if(radio_single->isChecked()){
    	for(int i=0;(unsigned)i<input.size();i++){
    		if(isspace(input[i])){
    			if((unsigned)i==input.size()-1)
    				input=input.substr(0,i);
    			else{
    				input=input.substr(0,i)+input.substr(i+1);
    			}
    			i--;
    		}
    	}
        search_single(lowerCase(input));
    }
    else {
        std::vector<std::string> input_words;
        unsigned int counter=0;
        while(counter<input.size()+1){
            if(counter==input.size()){ 
                if(input.substr(0,counter)!=""){
                    input_words.push_back(lowerCase(input.substr(0,counter)));
                }
                counter++;
            }
            else if(isspace(input[counter])){
                if(input.substr(0,counter)!=""){
                    input_words.push_back(lowerCase(input.substr(0,counter)));
                }

                if(counter+1<input.size()){
                    input=input.substr(counter+1);
                    counter=0;
                }
                else
                    counter++;
            }
            else{
                counter++;
            }
        }

        
        if(radio_and->isChecked()){
            search_and(input_words);
        }
        else if(radio_or->isChecked()){
            search_or(input_words);
        }
    }
    //populate the main search result list after searching
    populate_mainList();
}
//The user changed the sort type, repopulate the list if there are results.
void SearchUI::mainList_sortType_clicked(){
    if(search_result.size()==0)
        return;
    populate_mainList();
}
//The user clicked an item in the main search result list
void SearchUI::mainList_item_clicked(int itemRow){
    if(itemRow<0)
        return;

    //repopulate everything on the sub-window
    WebPage* wp= mainList_data.at(itemRow);
    populate_nameDisplay( wp );
    populate_contentDisplay(wp);
    populate_inList(wp);
    populate_outList(wp);
    details_window->show();
}
//The user clicked the close butotn on the sub-window
void SearchUI::closeButton_clicked(){
    details_window->hide();
}
//The user changed the sort type, repopulate the list with NULL to signal there should be no change in the content. Only resorting the data.
void SearchUI::inList_sortType_clicked(){
    populate_inList(NULL);
}
//The user clicked an item in the incoming links list 
void SearchUI::inList_item_clicked(int itemRow){
    if(itemRow<0)
        return;
    //repopulate everything on the sub-window
    WebPage* wp= inList_data.at(itemRow);
    populate_nameDisplay( wp );
    populate_contentDisplay(wp);
    populate_inList(wp);
    populate_outList(wp);
}
//The user changed the sort type.
void SearchUI::outList_sortType_clicked(){
    populate_outList(NULL);
}
//The user clicked on an item in the outgoing links list
void SearchUI::outList_item_clicked(int itemRow){
    if(itemRow<0)
        return;
    //repopulate everything on the sub-window
    WebPage* wp= outList_data.at(itemRow);
    populate_nameDisplay( wp );
    populate_contentDisplay(wp);
    populate_inList(wp);
    populate_outList(wp);
}













//___________________PRIVATE FUNCTIONS__________________

//Populate the mainlist
void SearchUI::populate_mainList(){
	//Clear everything
    mainList->clear();
    mainList_data.clear();

    //Put the search result into an std::vector
    for(std::set<WebPage*>::iterator it = search_result.begin(); it != search_result.end(); ++it){
        mainList_data.push_back(*it);
    }

    //Sort it based on the current sort selection
    if(mainList_sortType->checkedButton()==mainList_pageRank_button)
        sort_pageRank(mainList_data);
    else if(mainList_sortType->checkedButton()==mainList_nameSort_button)
        sort_name(mainList_data);
    else if(mainList_sortType->checkedButton()==mainList_inLink_button)
        sort_inLink(mainList_data);
    else if(mainList_sortType->checkedButton()==mainList_outLink_button)
        sort_outLink(mainList_data);

    //Populate the list
    for(unsigned int i=0;i<mainList_data.size();i++){
        MainListItem* item= new MainListItem(mainList_data[i]);
        QListWidgetItem* lwi = new QListWidgetItem(mainList);
        lwi->setSizeHint(item->minimumSizeHint());
        mainList->addItem(lwi);       
        mainList->setItemWidget(lwi,item);
    }
}
//Populate the name display
void SearchUI::populate_nameDisplay(WebPage* wp){
    if(wp)
        nameDisplay->setText(QString::fromStdString(wp->filename()));
}
//Populate the webpage content display
void SearchUI::populate_contentDisplay(WebPage* wp){
    if(wp){
        std::stringstream ss;
        ss<< (*wp);
        webContent ->setText(QString::fromStdString(ss.str()));
    }

}
//Populate the incoming links list
void SearchUI::populate_inList(WebPage* wp){
    inList->clear();

    //If the passed in pointer is NULL, we don't change the data.
    if(wp){
        myset<WebPage*> incoming = wp->incoming_links();
        inList_data.clear();
        for(std::set<WebPage*>::iterator it = incoming.begin(); it != incoming.end(); ++it){
         inList_data.push_back(*it);
        }
    }
    //Sort
    if(inList_sortType->checkedButton()==inList_nameSort_button)
        sort_name(inList_data);
    else if(inList_sortType->checkedButton()==inList_inLink_button)
        sort_inLink(inList_data);
    else if(inList_sortType->checkedButton()==inList_outLink_button)
        sort_outLink(inList_data);
    //populate
    for(unsigned int i=0;i<inList_data.size();i++){
        ListItem* item= new ListItem(inList_data[i]);
        QListWidgetItem* lwi = new QListWidgetItem(inList);
        lwi->setSizeHint(item->minimumSizeHint());
        inList->addItem(lwi);
        inList->setItemWidget(lwi,item);
    }
}
//Populate the outgoing links list
void SearchUI::populate_outList(WebPage* wp){
    outList->clear();

    //We don't update the data if the passed in pointer is NULL
    if(wp){
        myset<WebPage*> outgoing = wp->outgoing_links();
        outList_data.clear();
        for(std::set<WebPage*>::iterator it = outgoing.begin(); it != outgoing.end(); ++it){
            outList_data.push_back(*it);
        }
    }

    //Sort
    if(outList_sortType->checkedButton()==outList_nameSort_button)
        sort_name(outList_data);
    else if(outList_sortType->checkedButton()==outList_inLink_button)
        sort_inLink(outList_data);
    else if(outList_sortType->checkedButton()==outList_outLink_button)
        sort_outLink(outList_data);

    //Populate
    for(unsigned int i=0;i<outList_data.size();i++){
        ListItem* item= new ListItem(outList_data[i]);
        QListWidgetItem* lwi = new QListWidgetItem(outList);
        lwi->setSizeHint(item->minimumSizeHint());
        outList->addItem(lwi);
        outList->setItemWidget(lwi,item);
    }
}

///Search a single input, the entire std::string
void SearchUI::search_single(std::string input){
    search_result.clear();
    search_result = sn.findWord(input);
}

//Search for pages that contain all words in the std::vector
void SearchUI::search_and(std::vector<std::string> input_words){
    search_result.clear();
    search_result = sn.findWord(input_words[0]);
    for(unsigned int i=1;i<input_words.size();i++){
        search_result = search_result.set_intersection(sn.findWord(input_words[i]));
    }
}
//search for all pages that contain any of words in the std::vector
void SearchUI::search_or(std::vector<std::string> input_words){
    search_result.clear();
    search_result = sn.findWord(input_words[0]);
    for(unsigned int i=1;i<input_words.size();i++){
        search_result = search_result.set_union(sn.findWord(input_words[i]));
    }           
}
//Sort by PageRank
void SearchUI::sort_pageRank(std::vector<WebPage*>& v){
    //Create nodes and graoh/std::map
    std::map<std::string,Node> graph;
    for(unsigned int i=0;i<v.size();i++){
        std::string name = v[i]->filename();
        Node newNode(name);
        // Add self loop
        newNode.incoming_links.insert(name);        
        newNode.outgoing_links.insert(name);
        //Import data from std::vector into nodes, but only ones that are candidate
        myset<WebPage*> inc = v[i]->incoming_links();
        for(myset<WebPage*>::iterator it = inc.begin();it!=inc.end();it++){
            if(isCandidate(*it,v))
                newNode.incoming_links.insert((*it)->filename());
        }
        myset<WebPage*> out = v[i]->outgoing_links();    
        for(myset<WebPage*>::iterator it = out.begin();it!=out.end();it++){
            if(isCandidate(*it,v))
                newNode.outgoing_links.insert((*it)->filename());
        } 
        //Populate graph
        graph[name] = newNode;
    }
    //Calculate pagerank for every node in the graph
    graph = calculate_pageRank(graph);
    //Create a comparator with the graph
    webpage_pageRank_comp comp;
    comp.setGraph(graph);
    //Sort the vector of webpages with the graph.
    mergeSort(v,comp);
}
bool SearchUI::isCandidate(WebPage* wp, std::vector<WebPage*>& v){
    for(unsigned int i=0;i<v.size();i++){
        if( wp->filename() == ((v[i])->filename()) )
            return true;
    }
    return false;
}
std::map<std::string,Node> SearchUI::calculate_pageRank(std::map<std::string,Node> graph){
	std::map<std::string,Node> result = graph;
    for(std::map<std::string,Node>::iterator it = result.begin();it!=result.end();it++){
        (it->second).pageRank = (double)1/result.size();
    }

    //t steps
    for(int i=0;i<step_number;i++){
        //Every step, every node
        std::map<std::string, double> map_link_pr;
        std::map<std::string,Node>::iterator it;
        for(it = result.begin();it!=result.end();it++){
            //Every node's every incoming
            Node current = (it->second);
            std::set<std::string> inc = current.incoming_links;
            double sum = 0;
            for(std::set<std::string>::iterator it2 = inc.begin();it2!=inc.end();it2++){
                sum = sum + (result[*it2].pageRank) / (result[*it2].outgoing_links.size());
            }
            map_link_pr[(it->first)] = ((double)1-restart_probability)*sum +((double)1/result.size())*restart_probability;

        }    
        
        //This makes sure we don't update the current page's pagerank until every page has their to-be page rank calculated. 
        for(it = result.begin();it!=result.end();it++){
        	(it->second).pageRank = map_link_pr[it->first];
        }
    }
    return result;
}
//Sort by file name
void SearchUI::sort_name(std::vector<WebPage*>& v){
     webpage_filename_comp comp;
     mergeSort(v, comp);
}
//Sort by the number of incoming links
void SearchUI::sort_inLink(std::vector<WebPage*>& v){
     webpage_inLink_comp comp;
     mergeSort(v, comp);
}
//Sort by the number of outgoing links
void SearchUI::sort_outLink(std::vector<WebPage*>& v){
     webpage_outLink_comp comp;
     mergeSort(v, comp);

}
//Convert a std::string's alphabets to all lower case for standardization.
std::string SearchUI::lowerCase(std::string s){
    unsigned int i=0;
    while (i<s.size()){
        if(isalpha(s[i]))
            s[i]=tolower(s[i]);
        i++;
    }
    return s;
}