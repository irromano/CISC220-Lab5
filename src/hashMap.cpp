//============================================================================
// Ian Romano, Michael Richards
// TA: Daniel Gaston
// 5/09/19
//
// hashMap.cpp
//============================================================================

#include "hashMap.hpp"

 // when creating the map, make sure you initialize the values to NULL so you know whether that index has a key in it or not already.
//The Boolean values initialize the h1 and the c1 boolean values, making it easier to control which hash and which collision methods you use.
hashMap::hashMap(bool hash1, bool coll1) {

	first = "";
	numKeys = NULL;
	mapSize = 7;
	*map = new hashNode[mapSize];
	for (int i=0; i<7; i++) {
		map[i] = NULL;
	}
	this->hash1 = hash1;
	this->coll1 = coll1;

}

/*
 * adds a node  to the map at the correct index based on the key string, and then inserts the value into the value field of the hashNode
 * Must check to see whether there's a node at that location.  If there's nothing there (it's NULL), add the hashNode with the keyword and value.
 * If the node has the same keyword, just add the value to the list of values.
 * If the node has a different keyword, keep calculating a new hash index until either the keyword matches the node at that index's keyword, or until the
 * map at that index is NULL, in which case you'll add the node there.
 * This method also checks for load, and if the load is over 70%, it calls the reHash method to create a new longer map array and rehash the values
 * if h1 is true, the first hash function is used, and if it’s false, the second is used.
 * if c1 is true, the first collision method is used, and if it’s false, the second is used
 */
//void hashMap::addKeyValue(string key, string value);

// uses calcHash and reHash to calculate and return the index of where the keyword k should be inserted into the map array
int hashMap::getIndex(string key) {
	if (hash1) {
		return calcHash(key);
	} else {
		return calcHash2(key);
	}
}

/*	calcHash
 *  The first string hashing function. This divides the string into characters, converts them to ASCII ints, and
 *  sums them in-order using a complicated formula. Each integer is added with the previous integer multiplied by a base (17)
 *  and moduled by the mapSize.
 * 	Parameters:
 * 		string key: This is the string representing the value to be stored.
 * 	Returns:
 * 		int segment: This is the index representing the key for the value.
 */
int hashMap::calcHash(string key) {
	int base = 17;
	int len = key.length();
	int segment = 0;
	for (int i=0; i<len; i++) {
		segment = ((segment * base + int(key[i])) % this->mapSize);
	}
	return segment;
}

/*	calcHash2
 *  The second string hashing function. This divides the string into characters, converts them to ASCII ints, and
 *  sums them in reverse-order using a complicated formula. Each integer is added with the last integer multiplied by a base (13)
 *  and moduled by the mapSize.
 * 	Parameters:
 * 		string key: This is the string representing the value to be stored.
 * 	Returns:
 * 		int segment: This is the index representing the key for the value.
 */
int hashMap::calcHash2(string key) {
	int base = 13;
	int len = key.length();
	int segment = 0;
	for (int i= len -1; i > -1; i--) {
		segment = ((segment * base + int(key[i])) % this->mapSize);
	}
	return segment;
}
/* getClosestPrime()
 * This method takes in an int and returns the next closest prime.
 * It uses recursion.
 * Parameters:
 * 		int mapSize: and int representing the new mapSize after the double.
 * Returns:
 * 		int: mapSize if mapSize is already a prime number. Otherwise it's
 * 			the next prime number.
 */
int hashMap::getClosestPrime(int mapSize) {
	if (mapSize < 2)
		mapSize = 2;
	for (int i = mapSize -1; i>1; i--) {
		if (mapSize % i == 0) {
			return this->getClosestPrime(mapSize + 1);
		}
	}
	return mapSize;
}

// when size of array is at 70%, double array size and rehash keys
void hashMap::reHash() {
	int newMapSize = getClosestPrime(mapSize * 2);
	hashNode **newMap;
	*newMap = new hashNode[newMapSize];
	for (int i=0; i<newMapSize; i++) {
		newMap[i] = NULL;
	}

	for (int i = 0; i < mapSize; i++) {
		if (map[i] != NULL) {
			string keyword = map[i]->keyword;
			int hash;
			if (hash1) {
				hash = calcHash(keyword);
			} else {
				hash = calcHash2(keyword);
			}
			newMap[hash] = map[i];
		}
	}


}

/*collHash1() (Linear Probing)
 * This collision handling method uses linear probing and recursion to return the next index.
 * Parameters:
 * 		int h: represents the amount of times collHash1 was called.
 *			If using this method manually, this should be set to 0;
 * 		int index: represents the current index being looked at. If being manually called by
 * 			the user, a value of the collision index plus 1 should be used.
 * 		string key: represents the keyword to be inserted.
 *
 */
int hashMap::collHash1(int h, int index, string key) {
	h++;
	if (map[index] == NULL) {
		return index;
	} else {
		if (index >= mapSize -1) {
			index = -1;
		}
		return collHash1(h, index +1, key);
	}
}

/*collHash2() (Quadratic Probing)
 * This collision handling method uses quadratic probing and recursion to return the next index.
 * Parameters:
 * 		int h: represents the amount of times collHash2 was called. Used for Quadratic Calculation.
 * 				If using this method manually, this should be set to 0;
 * 		int index: represents the current index being looked at. If being manually called by
 * 			the user, a value of the collision index plus 1 should be used.
 * 		string key: represents the keyword to be inserted.
 *
 */
int hashMap::collHash2(int h, int index, string key) {
	h++;
	if (map[index] == NULL) {
		return index;
	} else {
		index += h * h;
		while (index >= mapSize) {
			index -= mapSize;
		}
		return collHash2(h, index, key);
	}
}

//finds the key in the array and returns its index.  If it's not in the array, returns -1
//int hashMap::findKey(string key);

//I wrote this solely to check if everything was working.
//void hashMap::printMap();

