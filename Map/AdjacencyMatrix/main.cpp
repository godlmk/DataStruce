#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	Graph G("g.txt");
	G.print();
	cout << "��С������Ϊ��\n";
	G.prim(0);
	return 0;
}