#include "BinaryTree.h"
#include <iostream>

using namespace std;

int main() {
	Tree t;
	t.CreateTree();
	t.In();
	cout << endl;
	cout << t.Depth();
	return 0;
}