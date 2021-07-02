#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>
using namespace std;
class Graph {
public:
	Graph(string filename)
	{
		ifstream file(filename);
		assert(file.is_open());
		string line;
		assert(getline(file, line));
		stringstream ss(line);
		ss >> V >> E;
		visted.resize(V, false);
		for (int i = 0; i < V; ++i) adj.push_back(vector<int>(V, INT32_MAX));
		for (int i = 0; i < E; ++i)
		{
			assert(getline(file, line));
			stringstream ss(line);
			int a, b, c;
			ss >> a >> b >> c;
			adj[a][b] = c;
			adj[b][a] = c;
		}
	}
	bool hasEdge(int v, int w)
	{
		return adj[v][w] == 1;
	}
	vector<int> adjV(int v)
	{
		vector <int> ans;
		for (int i = 0; i < V; ++i) {
			if (adj[v][i])
				ans.emplace_back(i);
		}
		return ans;
	}

	void prim(int u)
	{
		vector<pair<int, int>> closedge(V);
		//初始化closedge数组，第一项为与之相连最短节点的节点下标，第二项为与这个节点的距离
		for (int i = 0; i < V; ++i)
		{
			if (i != u)
				closedge[i] = { u, adj[u][i] };
		}
		//当closedge[i].second == 0时，代表i已经加入了树中
		closedge[u].second = 0;
		int count = V;
		//循环V - 1 次，将所有的顶点都添加到树中
		while (--count)
		{
			int shortDistance = INT32_MAX, shortI = -1;
			//找到在树中的节点和树外的节点的最短距离，即closedge[i].second > 0
			for (int i = 0; i < V; ++i)
				if (closedge[i].second && closedge[i].second < shortDistance)
				{
					shortDistance = closedge[i].second;
					shortI = i;
				}
			auto anothI = closedge[shortI].first;
			cout << shortI << " - " << anothI << " " << adj[shortI][anothI] << endl;
			//将shortI加入到树中
			closedge[shortI].second = 0;
			/*
			如果新增的节点shortI与树外的节点能使closedge数组的值变小则更新,
				（因为不存在权值为0的边，所以不会更新已经加入树中的节点）
			*/
			for (int i = 0; i < V; ++i)
			{
				if (adj[shortI][i] < closedge[i].second)
					closedge[i] = { shortI, adj[shortI][i] };
			}
		}
	}
	void dijkstra(int u)
	{
	}
	void dfs(int v)
	{
		cout << v << " ";
		visted[v] = true;
		for (int i = 0; i < V; ++i)
			if (!visted[i] && adj[v][i]) dfs(i);
	}
	void bfs(int v)
	{
		for (int i = 0; i < visted.size(); ++i) visted[i] = false;
		visted[v] = true;
		queue<int> que;
		que.push(v);
		while (!que.empty())
		{
			int t = que.front();
			que.pop();
			cout << t << " ";
			for (int i = 0; i < V; ++i)
				if (adj[t][i] && !visted[i])
				{
					que.push(i);
					visted[i] = true;
				}
		}
	}
	void bfsAll()
	{
		for (int i = 0; i < visted.size(); ++i) visted[i] = false;
		for (int i = 0; i < adj.size(); ++i) if (!visted[i]) bfs(i);
	}
	void dfsAll()
	{
		for (int i = 0; i < visted.size(); ++i) visted[i] = false;
		for (int i = 0; i < adj.size(); ++i) if (!visted[i]) dfs(i);
	}
	void print()
	{
		for (int i = 0; i < V; ++i)
		{
			for (int j = 0; j < V; ++j)
				if (adj[i][j] != INT32_MAX)
					printf("%d\t", adj[i][j]);
				else printf("∞\t");
			printf("\n");
		}
	}
private:
	int V, E;
	vector<vector<int>> adj;
	vector<bool> visted;
};