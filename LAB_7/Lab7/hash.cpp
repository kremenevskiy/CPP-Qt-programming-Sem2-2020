#include "hash.h"


Hash::Hash()
{
	for(int i = 0; i < hashTableSize; ++i){
		HashTable[i] = new Item;
		HashTable[i]->value = "NULL";
		HashTable[i]->next = nullptr;

	}

}


int Hash::hash(QString key){
	int hash = 0;
	for(int i = 0; i < key.length(); ++i){
		hash += (int) key[0].toLatin1();
	}

	hash %= hashTableSize;
	return hash;

}


void Hash::addItem(QString value){
	int index = hash(value);

	if(HashTable[index]->value == "NULL"){
		HashTable[index]->value = value;
	}
	else{
		Item *current = HashTable[index];
		Item *newItem = new Item;
		newItem->value = value;
		newItem->next = nullptr;

		while(current->next){
			current = current->next;
		}

		current->next = newItem;


	}

	emit addedItem();
}


Item *Hash::findItem(QString value){
	int index = hash(value);
	bool isExists = false;

	Item* current = HashTable[index];
	while (current) {
		if(current->value == value){
			isExists = true;
			return current;
		}
		current = current->next;
	}

	return nullptr;
}


void Hash::removeItem(QString value){
	int index = hash(value);

	Item *head = HashTable[index];
	Item *current = head->next;


	if(head->value == value){
		if(!head->next){
			head->value = "NULL";
			emit removedItem();
			return;
		}
		Item *oldHead = head;
		HashTable[index] = HashTable[index]->next;
		delete oldHead;

		emit removedItem();
		return;
	}

	Item* prev = head;
	while(current){
		if(current->value == value){
			prev->next = current->next;
			delete current;
			emit removedItem();
			return;
		}
		current = current->next;
		prev = prev->next;
	}

}


int Hash::numberOfItemsInIndex(int index){
	int count = 0;

	Item* current = HashTable[index];

	while(current->next){
		count ++;
		current = current->next;
	}

	return count;
}


QString Hash::printItemsInIndex(int index){
	QString bucketValues = QString::number(index) + ". ";

	Item *current = HashTable[index];
	while(current){
		bucketValues += " -> " + current->value;
		current = current->next;
	}
	return bucketValues;
}
