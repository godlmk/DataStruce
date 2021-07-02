#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	const string filename1 = "有向连通图.txt", filename2 = "无向连通图.txt",
		filename3 = "拓扑排序.txt";
	Graph G{ filename1 };
	G.print();
	puts("最小生成树为：");
	G.prim(0);
	auto dij = G.Dijkstra(0);
	string shortpath;
	for (int i = static_cast<int>(dij.size() - 1); i >= 0;)
	{
		shortpath += (i + '0');
		if (i)
			shortpath += "  >- ";
		i = dij[i];
	}
	reverse(shortpath.begin(), shortpath.end());
	cout << "最短路径为：" << shortpath;
	return 0;
}