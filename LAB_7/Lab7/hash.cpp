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

	if(!HashTable[index]->next){
		HashTable[index]->value = value;
	}
	else{
		Item *current = HashTable[index];
		Item *newItem = new Item;
		newItem->value = value;
		newItem->next = nullptr;

		while(!current->next){
			current = current->next;
		}

		current->next = newItem;


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
