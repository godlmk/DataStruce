#include <iostream>
#include "Graph.h"
using namespace std;

int main() {
	const string filename1 = "������ͨͼ.txt", filename2 = "������ͨͼ.txt",
		filename3 = "��������.txt";
	Graph G{ filename1 };
	G.print();
	puts("��С������Ϊ��");
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
	cout << "���·��Ϊ��" << shortpath;
	return 0;
}