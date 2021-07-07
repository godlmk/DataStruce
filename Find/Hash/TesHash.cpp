#include <iostream>
#include "ChainAddress.h"

using namespace std;

int main() {
	ChainHash ch;
	for (int i = 1; i < 11; ++i) ch.Insert(i);
	ch.Delete(5);
	for (int i = 1; i < 20; i += 2)
		if (ch.Find(i)) cout << "Yes" << endl;
		else cout << "No" << endl;
	return 0;
}