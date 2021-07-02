#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	Graph G{ "g.txt" };
	G.print();
	G.dfs(0);
	cout << endl;
	G.bfs(0);
	return 0;
}