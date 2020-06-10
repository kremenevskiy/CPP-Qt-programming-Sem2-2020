#ifndef RANDHASH_H
#define RANDHASH_H

#include "hash.h"
#include <QRandomGenerator>

class RandHash : public Hash
{
public:
	RandHash();
	static void randomizeHash(Hash **hashTable, int cnt);
	QString static randString(int count);

};

#endif // RANDHASH_H
