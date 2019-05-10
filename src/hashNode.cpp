/*
 * hashNode.cpp
 *
 *  Created on: May 9, 2019
 *      Author: ianro
 */

#include "hashNode.hpp"

hashNode::hashNode() {
	// TODO Auto-generated constructor stub

}

hashNode::~hashNode() {
	// TODO Auto-generated destructor stub
}

//creates a new array, double the length, and copies over the values. Sets the values array to be the newly allocated array.
void hashNode :: dblArray() {
	string dblArray = new string[2 * valuesSize];
	for (int i = 0; i < valuesSize; i++) {
		dblArray[i] = values[i];
	}
	valuesSize = 2 * valuesSize;
}

