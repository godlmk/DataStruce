#include <iostream>
#include "ChainAddress.h"

using namespace std;

int main() {
	ChainHash ch;
	for (int i = 1; i < 11; ++i) ch.Insert(i);
	for (int i = 1; i < 11; ++i) ch.Insert(i);

	ch.Delete(5);
	ch.print();
	return 0;
}