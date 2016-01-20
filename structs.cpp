#include <string>
#include <map>
#include "webpage.h"

//Page rank node
struct Node{
    Node(){}
    Node(std::string name){
        webpage_name = name;
    }
    std::string webpage_name;
    std::set<std::string> incoming_links;
    std::set<std::string> outgoing_links;
    double pageRank;
};

//Merge Sort Comparators
struct webpage_filename_comp {
    bool operator()(const WebPage* lhs, const WebPage* rhs){ 
        return lhs->filename() <= rhs->filename(); 
    }
};

struct webpage_inLink_comp {
    bool operator()(const WebPage* lhs, const WebPage* rhs){ 
        return lhs->incoming_links().size() <= rhs->incoming_links().size(); 
    }
};

struct webpage_outLink_comp {
    bool operator()(const WebPage* lhs, const WebPage* rhs){ 
        return lhs->outgoing_links().size() <= rhs->outgoing_links().size(); 
    }
};

struct webpage_pageRank_comp {
    void setGraph(std::map<std::string,Node> g){
        graph=g;
    }

    bool operator()(const WebPage* lhs, const WebPage* rhs){ 

        return graph[lhs->filename()].pageRank > graph[rhs->filename()].pageRank; 
    }
    std::map<std::string,Node> graph;
};