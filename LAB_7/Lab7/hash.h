#ifndef HASH_H
#define HASH_H

#include <QString>
#include <QDebug>



class Hash
{
public:
	struct Item{
		QString value;
		Item *next;
	};

	Hash();
	static const int hashTableSize = 10;

	Item* HashTable[hashTableSize];

	int hash(QString key);
	void addItem(QString value);

	int numberOfItemsInIndex(int index);
	Item* findItem(	 )




private:

};

#endif // HASH_H
