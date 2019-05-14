//============================================================================
// Name        : DrSeuss.cpp
// Author      : Ray
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;
#include "hashMap.hpp"

int main() {

	hashMap *testMap = new hashMap(1, 0);
	testMap->printMap();
	int ind1 = testMap->calcHash("cad");
	int ind2 = testMap->collHash2(0, 6, "don");
	cout << ind1 << endl;
	cout << ind2 << endl;
	return 0;
}
