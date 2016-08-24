# Project-Text-File-Search-Engine



This is the readme file for my text file search engine.
The files in this folder are as follows:

**data(folder)**: This folder is a subdirectory data folder to store the data used in the search engine, as well as the **seed** file for the crawler and the **index** file, which is the output file of the crawler and index file of the search engine. 

**config.txt**: This is the default configuration filename for the search engine.

**config_crawler.txt**: This is the default configueration filename for the crawler.

**crawler.cpp**: This file contains the crawler application. Enter the following command to compile it:

>*g++ -g -Wall crawler.cpp -o crawler*

Enter the following command to run it:

>*./crawler*

**hw6.pro**: This is the .pro file for this assignment.

**listitem.cpp** and **listitem.h**: These files define a customized list class that will go into the QListWidgets in searchUI.cpp to display the webpages' filenames, number of incoming links, and number of outgoing links.

**mainlistitem.cpp** and **mainlistitem.h**: These files define a customized list class that is very similar to the listitem.cpp and .h files. The only difference is that the filename QLabel is extended here so that the name looks like it goes across both the name sort and pagerank sort radio buttons. 

**mdparser.cpp** and **mdparser.h**: These files define a simplified MDParser class. With an abstract PageParser class featuring a parse function, my search engine is able to support alternate file formats (MD, HTML, etc.)

**msort.h**: This file contains the implementation of a templated mergesort

**myset.h**: This file defines a templated subclass of std::set class that feature the functions set_intersection and set_union.

**pageparser.h**: This file defines an abstract PageParsser class for the current MDParser class and future parsers to inherit from

**README.md**: This is the readme file

**search.cpp**: This files contains the implementation for the main user interface logic which will use the terminal and perform text-based queries via cin/cout. In the future I will replace this interface with a graphical user interface. To support that cleanly, the interface logic and the actual search logic are separated. To facilitate that, I will define a new SearchEng (Search Engine) class

**searcheng.cpp** and **searcheng.h**: These files define the SearchEng class mentioned above in the #search.cpp section. This class stores all the webpages and other indexing data and also performs the search operations and returns the appropriate WebPages.

**searchUI.cpp** and **searchUI.h**: These files define the SearchUI class, which is the main window for the application implemented on Qt. *When parsing search inputs, I made it so that if the user's search query specifies a single word, the search would ignore any spaces in the search term.* This is because it is not logical for the user to include spaces in a search type that specifies a single word.

**structs.cpp**: This file contains all the webpage comparators as well as the Node struct used for page rank.

**webpage.cpp** and **webpage.h**: These files define the WebPage class that stores the data and prepare it for either search and/or display after parsing a webpage. 



# Project-Text-File-Search-Engine
