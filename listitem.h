#ifndef LIST_ITEM_H
#define LIST_ITEM_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "webpage.h"

class ListItem : public QWidget {
	Q_OBJECT

	public:
		ListItem();
		ListItem(WebPage* webp);
		~ListItem();

	private:
		QHBoxLayout* layout;
		QLabel* filename;
		QLabel* numIncoming;
		QLabel* numOutgoing;
};

#endif