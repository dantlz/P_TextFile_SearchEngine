#ifndef MAINLIST_ITEM_H
#define MAINLIST_ITEM_H
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include "webpage.h"

class MainListItem : public QWidget {
	Q_OBJECT

	public:
		MainListItem();
		MainListItem(WebPage* webp);
		~MainListItem();

	private:
		QHBoxLayout* layout;
		QLabel* filename;
		QLabel* numIncoming;
		QLabel* numOutgoing;
};

#endif
