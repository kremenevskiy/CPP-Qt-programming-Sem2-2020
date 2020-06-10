#include "randhash.h"

RandHash::RandHash()
{

}


void RandHash::randomizeHash(Hash **hashTable, int cnt){
	for(int i = 0; i < cnt; ++i){
		QString randStr = randString(7);

		if ((*hashTable)->hash(randStr) % 2 != 0){
			continue;
		}
		(*hashTable)->addItem(randStr);
	}
}


QString RandHash::randString(int count){
	QString randStr;
	for(int i = 0; i < count; ++i){
		int num = QRandomGenerator::global()->generate() % 26;
		char ch = (char) num + 97;
		randStr.append(ch);
	}

	return randStr;
}
