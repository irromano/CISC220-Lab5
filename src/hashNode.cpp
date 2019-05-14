//============================================================================
// Ian Romano, Michael Richards
// TA: Daniel Gaston
// 5/09/19
//
// hashNode.cpp
//============================================================================


#include "hashNode.hpp"


//constructor-initializes keyword to “” , valuesSize to 0, and currSize to 0 and values to NULL
hashNode::hashNode() {
	keyword = "";
	valuesSize = 0;
	currSize = 0;
	values = NULL;

}
// initializes keyword to s, the valuesSize to 100 (or whatever you like for starting), the currSize to 0,
// and the values to be a dynamically allocated array of valuesSize.
hashNode::hashNode(string keyword) {

	this->keyword = keyword;
	valuesSize = 100;
	values = new string[valuesSize];
	currSize = 0;
}
// in addition to the single parameter constructor, this one puts a value in the values array and initializes currSize to 1
hashNode::hashNode(string keyword, string value) {
	this->keyword = keyword;
	valuesSize = 100;
	values = new string[valuesSize];
	values[0] = value;
	currSize = 1;
}

// adds a new value to the end of the values array, increases currSize, checks to make sure there’s more space,
// and, if not, calls dblArray()
void hashNode::addValue(string value) {

	if (valuesSize == 0) { //if values array is not initialized yet, initialize values.

		valuesSize = 100;
		values = new string[valuesSize];
	}

	values[currSize] = value;
	currSize++;

	if (currSize >= valuesSize) {
		dblArray();
	}

}
// returns a random string from the values array.  If there’s no values in the value array, then it returns an empty string.
string hashNode::getRandValue() {

	srand(time(NULL));
	if (currSize == 0) {
		return "";
	} else {
		srand(time(NULL));
		return values[rand() % currSize];
	}

}

//creates a new array, double the length, and copies over the values. Sets the values array to be the newly allocated array.
void hashNode::dblArray() {
	string *dblArray = new string[(2 * valuesSize)]; //Our new values array of double length
	for (int i = 0; i < valuesSize; i++) {					//for every value
		dblArray[i] = values[i];					//copy over values from old values to new values
	}
	valuesSize *= 2;										//double valuesSize
}

