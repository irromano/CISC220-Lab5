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
#include "makeSeuss.hpp"

int main() {

//	hashMap *testMap = new hashMap(1, 1);
//	testMap->addKeyValue("dog", "runs");
//	testMap->addKeyValue("cat", "runs");
//	testMap->addKeyValue("cat", "licks");
//	testMap->addKeyValue("cad", "licks");
//	testMap->addKeyValue("car", "licks");
//	testMap->printMap();
//	cout << endl;
//	testMap->addKeyValue("buggy", "off");
//	testMap->printMap();
	//cout << ind2 << endl;
	makeSeuss seuss("DrSeuss.txt", "TheNewHotness.txt", 1, 1);
	//seuss.writeFile();
	return 0;
}
