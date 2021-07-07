#include <iostream>
#include "Graph.h"
using namespace std;

int main()
{
	const string filename1 = "有向连通图.txt", filename2 = "无向连通图.txt",
		filename3 = "拓扑排序.txt";
	Graph G(filename1);
	puts("图的邻接矩阵表示如下：");
	G.print();
	if (!G.isDircete())
	{
		cout << "最小生成树为：\n";
		G.prim(0);
	}
	else
	{
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
		puts("\n拓扑排序为：");
		auto topo = G.TopologicalSort();
		for (const auto& x : topo) cout << x << " ";
		cout << "\n关键路径为：" << endl;
		G.CriticalPath();
	}
	return 0;
}