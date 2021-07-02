#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cassert>
#include <queue>
using namespace std;
class Graph {
public:
	Graph(string filename) {
		ifstream file(filename);
		assert(file.is_open());
		string line;
		assert(getline(file, line));
		stringstream ss(line);
		ss >> V >> E;
		adj.resize(V);
		visted.resize(V);
		for (int i = 0; i < V; ++i) {
			adj[i].next = nullptr;
			adj[i].data = i;
		}
		for (int i = 0; i < E; ++i) {
			assert(getline(file, line));
			stringstream ss(line);
			int a, b;
			ss >> a >> b;
			assert(a != b);                 // 没有自环边

			for (auto i = adj[a].next; i; i = i->next) assert(i->data != b);  // 没有平行边 （查重）

			auto tem1 = new Node{ b }, tem2 = new Node{ a };
			tem1->next = adj[a].next;
			adj[a].next = tem1;
			tem2->next = adj[b].next;
			adj[b].next = tem2;
		}
	}
	bool hasEdge(int v, int w) {
		auto p = adj[v].next;
		while (p) {
			if (p->data == w) return true;
		}
		return false;
	}
	vector<int> adjV(int v) {
		vector<int> ans;
		auto p = adj[v].next;
		while (p) {
			ans.emplace_back(p->data);
			p = p->next;
		}
	}
	void dfs(int v) {
		cout << v << " ";
		visted[v] = true;
		auto p = adj[v].next;
		while (p) {
			if (visted[p->data] == false) dfs(p->data);
			p = p->next;
		}
	}

	void bfs(int v) {
		queue<int> que;
		que.push(v);
		while (!que.empty()) {
			auto tem = que.front();
			que.pop();
			cout << adj[tem].data << " ";
			visted[tem] = true;
			auto p = adj[tem].next;
			while (p) {
				if (!visted[p->data])
					que.push(p->data);
				p = p->next;
			}
		}
	}
	void bfsAll() {
		for (int i = 0; i < visted.size(); ++i) visted[i] = false;
		for (int i = 0; i < adj.size(); ++i) if (!visted[i]) bfs(i);
	}
	void dfsAll() {
		for (int i = 0; i < visted.size(); ++i) visted[i] = false;
		for (int i = 0; i < adj.size(); ++i) if (!visted[i]) dfs(i);
	}
	void print() {
		for (const auto& line : adj) {
			auto p = line.next;
			while (p) { cout << p->data << " "; p = p->next; }
			cout << endl;
		}
	}
private:
	int V, E;
	struct Node {
		int data;
		Node* next;
	};
	vector<Node> adj;
	vector<bool> visted;
};