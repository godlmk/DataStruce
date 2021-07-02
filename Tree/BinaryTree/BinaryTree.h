#pragma once
#include <iostream>
class Tree
{
public:
	class node {
	public:
		node* left, * right;
		char data;
		node(char e) {
			data = e;
			left = right = nullptr;
		}
	};
	Tree();
	~Tree();
	void CreateTree(node* r);
	int getDepth();
	void destory();

private:
	class node {
	public:
		node* left, * right;
		char data;
		node(char e) {
			data = e;
			left = right = nullptr;
		}
	};
	node* root;
};

Tree::Tree()
{
	root->left = root->right = nullptr;
}

Tree::~Tree()
{
}

void Tree::CreateTree(node* r)
{
	char c;
	std::cin >> c;
	if (c == '#') r = nullptr;
	else {
		auto t = new node{ c };
		CreateTree(t->left);
		CreateTree(t->right);
	}
}
