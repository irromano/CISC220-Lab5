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
	numKeys = 0;
	mapSize = 10;

	map = new hashNode*[mapSize];
	for (int i=0; i<mapSize; i++) {
		map[i] = NULL;
	}
	this->hash1 = hash1;
	this->coll1 = coll1;

	collisionct1 = 0;
	collisionct2 = 0;

}

/*
 * adds a node  to the map at the correct index based on the key string, and then inserts the value into the value field of the hashNode
 * Must check to see whether there's a node at that location.  If there's nothing there (it's NULL), add the hashNode with the keyword and value.
 * If the node has the same keyword, just add the value to the list of values.
 * If the node has a different keyword, keep calculating a new hash index until either the keyword matches the node at that index's keyword, or until the
 * map at that index is NULL, in which case you'll add the node there.
 * This method also checks for load, and if the load is over 70%, it calls the reHash method to create a new longer map array and rehash the values
 * hashing and collision logic (hash1 vs hash2 and coll1 vs coll2) are handled by the getIndex() method.
 */
void hashMap::addKeyValue(string key, string value) {
	double load = (double(numKeys) +1.0) / mapSize;
	if (load > 0.70) {
		this->reHash();
	}
	int index = getIndex(key);
	if (map[index] == NULL) {
		map[index] = new hashNode(key, value);
		numKeys++;
	} else {
		map[index]->addValue(value);
	}
}

// uses calcHash and reHash to calculate and return the index of where the keyword k should be inserted into the map array
int hashMap::getIndex(string key) {
	int index;
	if (hash1) {
		index = calcHash(key);
	} else {
		index = calcHash2(key);
	}
	if (map[index] == NULL || map[index]->keyword == key) {
		return index;
	} else {
		collisionct1++;
		if (coll1) {
			index = collHash1(1, index +1, key);
		} else {
			index = collHash2(1, index +1, key);
		}
		return index;
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
	hashNode **oldMap = map;
	int oldMapSize = mapSize;
	mapSize = getClosestPrime(mapSize *2);
	map = new hashNode *[mapSize];

	for (int i=0; i<mapSize; i++) {
		map[i] = NULL;
	}

	for (int i=0; i<oldMapSize; i++) {
		if (oldMap[i] != NULL) {
			int index = this->getIndex(oldMap[i]->keyword);
			map[index] = oldMap[i];
			}
		}
	}


/*collHash1() (Linear Probing)
 * This collision handling method uses linear probing and recursion to return the next index.
 * Parameters:
 * 		int h: represents the amount of times collHash1 was called.
 *			If using this method manually, this should be set to 1;
 * 		int index: represents the current index being looked at. If being manually called by
 * 			the user, a value of the collision index plus 1 should be used.
 * 		string key: represents the keyword to be inserted.
 *
 */
int hashMap::collHash1(int h, int index, string key) {
	if (map[index] == NULL || map[index]->keyword == key) {
		return index;
	} else {
		h++;
		if (index >= mapSize -1) {
			index = -1;
		}
		collisionct2 += h +1;
		return collHash1(h, index +1, key);
	}
}

/*collHash2() (Quadratic Probing)
 * This collision handling method uses quadratic probing and recursion to return the next index.
 * Parameters:
 * 		int h: represents the amount of times collHash2 was called. Used for Quadratic Calculation.
 * 				If using this method manually, this should be set to 1;
 * 		int index: represents the current index being looked at. If being manually called by
 * 			the user, a value of the collision index plus 1 should be used.
 * 		string key: represents the keyword to be inserted.
 *
 */
int hashMap::collHash2(int h, int index, string key) {
	if (map[index] == NULL || map[index]->keyword == key) {
		return index;
	} else {
		h++;
		index += h * h;
		while (index >= mapSize) {
			index -= mapSize;
		}
		collisionct2 += h +1;
		return collHash2(h, index, key);
	}
}

//finds the key in the array and returns its index.  If it's not in the array, returns -1
int hashMap::findKey(string key) {
	int index;
	if (hash1) {
		index = calcHash(key);
	} else {
		index = calcHash2(key);
	}
	if (map[index] == NULL) {
		return -1;
	} else if (map[index]->keyword == key) {
		return index;
	} else {
		if (coll1) {
			index = collHash1(1, index +1, key);
		} else {
			index = collHash2(1, index +1, key);
		}
		if (map[index]->keyword == key) {
			return index;
		} else {
			return -1;
		}
	}
}


//I wrote this solely to check if everything was working.
void hashMap::printMap() {
	for (int i=0; i<mapSize; i++) {
		if (map[i] != NULL) {
			cout << "[" << i << "]" << map[i]->keyword << ": ";
			for (int j=0; j<map[i]->currSize; j++) {
				cout << map[i]->values[j] << " ";
			}
			cout << endl;
		} else {
			cout << "[" << i << "]" << "NULL" << endl;
		}
	}
	return;
}

