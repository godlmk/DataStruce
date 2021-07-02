#pragma once
#define MAX 10000
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>
#include <unordered_map>
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
		ss >> V >> E >> isDirected;
		adj.resize(V);
		visted.resize(V);
		for (int i = 0; i < E; ++i)
		{
			assert(getline(file, line));
			stringstream ss(line);
			int a, b, c;
			ss >> a >> b >> c;
			assert(a != b);              // 没有自环边
			adj[a].insert({ b,c });
			if (!isDirected)
				adj[b].insert({ a,c });
		}
	}
	bool hasEdge(int v, int w)
	{
		for (const auto& x : adj[v])
			if (x.first == w)
				return true;
		return false;
	}
	vector<int> adjV(int v)
	{
		vector<int> ans;

		for (const auto& x : adj[v])
			ans.emplace_back(x.first);
		return ans;
	}
	void prim(int u)
	{
		int k = u;
		vector<pair<int, int>> closedge(V, { u,MAX });
		for (const auto& x : adj[u])
			closedge[x.first] = { u, x.second };
		closedge[k].second = 0;
		int count = V;
		while (--count)
		{
			int minDistance = MAX, minI = -1;
			for (int i = 0; i < V; ++i)
				if (closedge[i].second && closedge[i].second < minDistance)
				{
					minI = i;
					minDistance = closedge[i].second;
				}
			int another = closedge[minI].first;
			closedge[minI].second = 0;
			cout << minI << " " << another << endl;
			for (const auto& x : adj[minI])
				if (x.second < closedge[x.first].second)
					closedge[x.first] = { minI, x.second };
		}
	}
	vector<int> Dijkstra(int u)
	{
		vector<bool> isPath(V, false);
		vector<int> distance(V, MAX), Path(V, -1);
		for (const auto& x : adj[u])
		{
			Path[x.first] = u;
			distance[x.first] = x.second;
		}
		isPath[u] = true;
		distance[u] = 0;
		int count = V;
		int minI = -1;
		while (--count)
		{
			int minDistance = MAX;
			for (int i = 0; i < V; ++i)
				if (!isPath[i] && distance[i] < minDistance)
				{
					minI = i;
					minDistance = distance[i];
				}
			isPath[minI] = true;
			for (const auto& x : adj[minI])
			
				if (!isPath[x.first] && distance[minI] + x.second < distance[x.first])
				{
					distance[x.first] = distance[minI] + x.second;
					Path[x.first] = minI;
				}
			
		}
		return Path;
	}
	void dfs(int v)
	{
		cout << v << " ";
		visted[v] = true;
		auto p = adj[v];
		for (auto& x : p)
			if (!visted[x.first]) dfs(x.first);
	}

	void bfs(int v)
	{
		queue<int> que;
		que.push(v);
		while (!que.empty())
		{
			auto p = que.front();
			que.pop();
			cout << p << " ";
			visted[p] = true;
			for (const auto& x : adj[p])
				if (!visted[x.first])
					que.push(x.first);
		}
	}
	void bfsAll()
	{
		visted = vector<bool>(V, false);
		for (int i = 0; i < adj.size(); ++i) if (!visted[i]) bfs(i);
	}
	void dfsAll()
	{
		visted = vector<bool>(V, false);
		for (int i = 0; i < adj.size(); ++i) if (!visted[i]) dfs(i);
	}
	void print()
	{
		for (const auto& line : adj)
		{
			for (const auto& x : line) cout << x.first << " ";
			cout << endl;
		}
	}
private:
	int V, E, isDirected = 0;
	vector<unordered_map<int, int>> adj;
	vector<bool> visted;
};