/*
 * hashNode.cpp
 *
 *  Created on: May 9, 2019
 *      Author: ianro
 */

#include <iostream>
#include <stdlib.h>
#include <string>
#include "hashNode.hpp"
#include <time.h>

hashNode::hashNode() {
	keyword = "";
	valuesSize = 0;
	currSize = 100;
	values = NULL;

}

hashNode::hashNode(string s) {

	s = keyword;
	valuesSize = 100;
	currSize = 0;
	string *arr = new string[valuesSize];
	values = arr;
}

hashNode::hashNode(string s, string v) {

	string *arr = new string[valuesSize];
	v = arr[0];
	currSize = 1;
}


void hashNode::addValue(string v) {

	if (valuesSize == 0) {

		valuesSize = 100;
		values = new string[valuesSize];
	}

	string *arr = new string[valuesSize];
	v = arr[currSize];
	currSize++;

	if (currSize >= valuesSize) {

		dblArray();
	}

}


string hashNode::getRandValue() {

	srand(time(NULL));
	if (currSize == 0) {

		return "";
	}

	else {

		return values[rand() % currSize];
	}

}

//creates a new array, double the length, and copies over the values. Sets the values array to be the newly allocated array.
void hashNode :: dblArray() {
	string *dblArray = new string[2 * valuesSize];
	for (int i = 0; i < valuesSize; i++) {
		dblArray[i] = values[i];
	}
	valuesSize = 2 * valuesSize;
}

