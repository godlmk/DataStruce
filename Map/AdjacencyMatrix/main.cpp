#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	Graph G("g.txt");
	G.print();
	cout << "最小生成树为：\n";
	G.prim(0);
	return 0;
}