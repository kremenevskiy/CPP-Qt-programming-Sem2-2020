#ifndef HASH_H
#define HASH_H

#include <QString>
#include <QDebug>
#include <QObject>

struct Item{
	QString value;
	Item *next;
};

class Hash : public QObject
{
	Q_OBJECT
public:

	Hash();
	static const int hashTableSize = 10;

	Item* HashTable[hashTableSize];

	int hash(QString key);
	void addItem(QString value);

	int numberOfItemsInIndex(int index);
	Item* findItem(QString value);
	void removeItem(QString value);

	QString printItemsInIndex(int index);

signals:
	void addedItem();
	void removedItem();

};

#endif // HASH_H
