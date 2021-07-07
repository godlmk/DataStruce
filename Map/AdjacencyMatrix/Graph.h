#pragma once
#define MAX 10000
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <sstream>
#include <string>
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
		ss >> V >> E >> isDircted;
		visted.resize(V, false);
		for (int i = 0; i < V; ++i) adj.push_back(vector<int>(V, MAX));
		for (int i = 0; i < E; ++i)
		{
			assert(getline(file, line));
			stringstream ss(line);
			int a, b, c;
			ss >> a >> b >> c;

			adj[a][b] = c;
			if (!isDircted)
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
		//图是连通图
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
		int shortI = -1;
		while (--count)
		{
			int shortDistance = MAX;
			//找到在树外的节点和树内的节点的最短距离的下标，且closedge[i].second > 0
			for (int i = 0; i < V; ++i)
				if (closedge[i].second && closedge[i].second < shortDistance)
				{
					shortDistance = closedge[i].second;
					shortI = i;
				}
			//shortI是新加入的点，anotherI是原来树中的点
			auto anotherI = closedge[shortI].first;
			//输出这两点
			cout << shortI << " - " << anotherI << " " << adj[shortI][anotherI] << endl;
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
	void Kruskal() {
		struct Edge
		{
			int from, des, weight;
			Edge(int a, int b, int c) : from{ a }, des{ b }, weight{ c }{}
		};
		vector<Edge> E;
		vector<int> Vexset(V);
		for (int i = 0; i < V; ++i) Vexset[i] = i;
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				E.emplace_back(Edge{ i, j,adj[i][j] });
		sort(E.begin(), E.end(), [](auto a, auto b) {return a.weight < b.weight; });
		for (int i = 0; i < V; ++i) {
			auto v1 = E[i].from, v2 = E[i].des;
			if (Vexset[v1] != Vexset[v2]) {
				cout << v1 << " " << v2 << endl;
				for (int j = 0; j < V; ++j)
					if (Vexset[j] == Vexset[v2]) Vexset[j] = Vexset[v1];
			}
		}
	}
	vector<int> Dijkstra(int u)
	{
		/*
			这个算法适合有向带权图
			将path初始化为 -1表示都没有前驱，
			distance初始化为和u的距离
		*/
		vector<int> Distance(V), Path(V, -1);
		vector<bool> S(V, false);
		S[u] = true;
		for (int v = 0; v < V; ++v)
		{
			Distance[v] = adj[u][v];
			if (Distance[v] < MAX) Path[v] = u;
		}
		Distance[u] = 0;
		int count = V;
		int minIndex = -1;
		//循环 V - 1次将剩下V - 1个结点加入进来
		while (--count)
		{
			int minDistance = MAX;
			//找到在s集合外和s集合相连的最小权值的节点下标
			for (int i = 0; i < V; ++i)

				if (!S[i] && Distance[i] < minDistance)
				{
					minIndex = i;
					minDistance = Distance[i];
				}
			S[minIndex] = true;
			/*
				若新节点的加入可以使s与s外的任意节点的距离变小，则更新他们的数据
				把距离更新同时把前驱也更新
			*/
			for (int w = 0; w < V; ++w)

				if (!S[w] && Distance[minIndex] + adj[minIndex][w] < Distance[w])
				{
					Distance[w] = Distance[minIndex] + adj[minIndex][w];
					Path[w] = minIndex;
				}
		}
		return Path;
	}
	vector<int> TopologicalSort()
	{
		//图为一个有向无环图
		vector<int> indegree(V, 0), topo(V);
		stack<int> stk;
		for (int i = 0; i < V; ++i)
			for (int j = 0; j < V; ++j)
				if (adj[j][i] < MAX) ++indegree[i];
		for (int i = 0; i < V; ++i) if (!indegree[i]) stk.push(i);
		int size = 0;
		while (!stk.empty())
		{
			auto top = stk.top();
			stk.pop();
			topo[size++] = top;
			queue<int> que;
			for (int i = 0; i < V; ++i) if (adj[top][i] < MAX) que.push(i);
			while (!que.empty())
			{
				auto p = que.front();
				que.pop();
				--indegree[p];
				if (!indegree[p]) stk.push(p);
			}
		}
		if (size < V) exit(-1);
		return topo;
	}
	void CriticalPath()
	{
		auto topo = TopologicalSort();
		//ve数组是最早开始时间，初始化为0
		vector<int> ve(V, 0);
		for (int i = 0; i < V; ++i)
		{
			int k = topo[i];
			vector<int> tem;
			//尝试更新所有以k结点为起点的弧，找到最大的那个ve[x]
			for (int j = 0; j < V; ++j)
				if (adj[k][j] < MAX)
					tem.emplace_back(j);
			for (const auto& x : tem)
				if (ve[x] < ve[k] + adj[k][x])
					ve[x] = ve[k] + adj[k][x];
		}
		//初始化vl数组为 ve数组的最后那个值
		vector<int> vl(V, ve.back());
		for (int i = V - 1; i >= 0; --i)
		{
			int k = topo[i];
			vector<int> tem;
			/*从后往前遍历，尝试将所有vl结点更新变得更小
			每次找到与k相连的结点中能使vl[k]变小的结点*/
			for (int j = 0; j < V; ++j)
				if (adj[k][j] < MAX)
					tem.emplace_back(j);
			for (const auto& x : tem)
				if (vl[k] > vl[x] - adj[k][x])
					vl[k] = vl[x] - adj[k][x];
		}
		for (int i = 0; i < V; ++i)
		{
			vector<int> tem;
			for (int j = 0; j < V; ++j)
				if (adj[i][j] < MAX)
					tem.emplace_back(j);
			for (const auto& x : tem)
				if (ve[i] == vl[x] - adj[i][x])
					cout << i << " " << x << endl;
		}
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
				if (adj[i][j] != MAX)
					printf("%d\t", adj[i][j]);
				else printf("∞\t");
			printf("\n");
		}
	}
	bool isDircete() { return isDircted; }
private:
	int V{ 0 }, E{ 0 }, isDircted = 0;
	vector<vector<int>> adj;
	vector<bool> visted;
};