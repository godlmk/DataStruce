#include <iostream>
#include "AVL.h"
using namespace std;

int main() {
	AVL a;
	a.Insert(2);
	a.Insert(11);
	a.Insert(1);
	a.Insert(-1);
	a.Insert(10);
	a.Insert(6);
	a.Insert(9);
	a.Insert(5);
	a.Insert(0);
	a.PreOrderTraverse();
	a.InorderTraverse();
	return 0;
}