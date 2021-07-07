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
		//ͼ����ͨͼ
		vector<pair<int, int>> closedge(V);
		//��ʼ��closedge���飬��һ��Ϊ��֮������̽ڵ�Ľڵ��±꣬�ڶ���Ϊ������ڵ�ľ���
		for (int i = 0; i < V; ++i)
		{
			if (i != u)
				closedge[i] = { u, adj[u][i] };
		}
		//��closedge[i].second == 0ʱ������i�Ѿ�����������
		closedge[u].second = 0;
		int count = V;
		//ѭ��V - 1 �Σ������еĶ��㶼��ӵ�����
		int shortI = -1;
		while (--count)
		{
			int shortDistance = MAX;
			//�ҵ�������Ľڵ�����ڵĽڵ����̾�����±꣬��closedge[i].second > 0
			for (int i = 0; i < V; ++i)
				if (closedge[i].second && closedge[i].second < shortDistance)
				{
					shortDistance = closedge[i].second;
					shortI = i;
				}
			//shortI���¼���ĵ㣬anotherI��ԭ�����еĵ�
			auto anotherI = closedge[shortI].first;
			//���������
			cout << shortI << " - " << anotherI << " " << adj[shortI][anotherI] << endl;
			//��shortI���뵽����
			closedge[shortI].second = 0;
			/*
			��������Ľڵ�shortI������Ľڵ���ʹclosedge�����ֵ��С�����,
				����Ϊ������ȨֵΪ0�ıߣ����Բ�������Ѿ��������еĽڵ㣩
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
			����㷨�ʺ������Ȩͼ
			��path��ʼ��Ϊ -1��ʾ��û��ǰ����
			distance��ʼ��Ϊ��u�ľ���
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
		//ѭ�� V - 1�ν�ʣ��V - 1�����������
		while (--count)
		{
			int minDistance = MAX;
			//�ҵ���s�������s������������СȨֵ�Ľڵ��±�
			for (int i = 0; i < V; ++i)

				if (!S[i] && Distance[i] < minDistance)
				{
					minIndex = i;
					minDistance = Distance[i];
				}
			S[minIndex] = true;
			/*
				���½ڵ�ļ������ʹs��s�������ڵ�ľ����С����������ǵ�����
				�Ѿ������ͬʱ��ǰ��Ҳ����
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
		//ͼΪһ�������޻�ͼ
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
		//ve���������翪ʼʱ�䣬��ʼ��Ϊ0
		vector<int> ve(V, 0);
		for (int i = 0; i < V; ++i)
		{
			int k = topo[i];
			vector<int> tem;
			//���Ը���������k���Ϊ���Ļ����ҵ������Ǹ�ve[x]
			for (int j = 0; j < V; ++j)
				if (adj[k][j] < MAX)
					tem.emplace_back(j);
			for (const auto& x : tem)
				if (ve[x] < ve[k] + adj[k][x])
					ve[x] = ve[k] + adj[k][x];
		}
		//��ʼ��vl����Ϊ ve���������Ǹ�ֵ
		vector<int> vl(V, ve.back());
		for (int i = V - 1; i >= 0; --i)
		{
			int k = topo[i];
			vector<int> tem;
			/*�Ӻ���ǰ���������Խ�����vl�����±�ø�С
			ÿ���ҵ���k�����Ľ������ʹvl[k]��С�Ľ��*/
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
				else printf("��\t");
			printf("\n");
		}
	}
	bool isDircete() { return isDircted; }
private:
	int V{ 0 }, E{ 0 }, isDircted = 0;
	vector<vector<int>> adj;
	vector<bool> visted;
};