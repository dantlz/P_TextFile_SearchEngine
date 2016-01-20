#include <QString>
#include <QFont>
#include <iostream>
#include "listitem.h"

ListItem::ListItem(){
	
}

ListItem::ListItem(WebPage* webp){
	layout = new QHBoxLayout();
	filename = new QLabel(QString::fromStdString(webp->filename()));
	filename->setFixedWidth(150);
	numIncoming = new QLabel(QString::number(webp->incoming_links().size()));
	numOutgoing = new QLabel(QString::number(webp->outgoing_links().size()));
	layout->addWidget(filename);
	layout->addWidget(numIncoming);
	layout->addWidget(numOutgoing);
	setLayout(layout);
}

ListItem::~ListItem() {
	delete filename;
	delete numOutgoing;
	delete numIncoming;
	delete layout;
}