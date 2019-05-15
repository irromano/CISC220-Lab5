//============================================================================
// Name        : Lab5Main.cpp
// Author      : Ian Romano, Michael Richards
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
using namespace std;
#include "hashMap.hpp"
#include "makeSeuss.hpp"

int main() {
	srand(time(NULL));

	makeSeuss seussH1C1("DrSeuss.txt", "hash1coll1.txt", true , true);
	makeSeuss seussH2C1("DrSeuss.txt", "hash2coll1.txt", false , true);
	makeSeuss seussH1C2("DrSeuss.txt", "hash1coll2.txt", true , false);
	makeSeuss seussH2C2("DrSeuss.txt", "hash2coll2.txt", false , false);
	return 0;
}
