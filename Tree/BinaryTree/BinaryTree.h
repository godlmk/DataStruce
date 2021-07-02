#pragma once
#include <iostream>
using std::cout, std::cin, std::endl;
class Tree
{
private:
	typedef struct Node {
		char data;
		Node* left, * right;
		Node(char e)
		{
			data = e;
			left = right = nullptr;
		}
	}*BTree;
	BTree root = new Node('r');
	void Create(BTree& t);
public:
	void CreateTree();
	~Tree();
	Tree();
	void InOrderTraverse(BTree t);
	void PreOrderTraverse(BTree t);
	void PostOrderTraverse(BTree t);
	void Pre();
	void Post();
	void In();
	int Depth();
	int getDepth(BTree t);
};
void Tree::CreateTree()
{
	Create(root);
}
inline Tree::~Tree()
{
}
inline Tree::Tree()
{
}
inline void Tree::InOrderTraverse(BTree t)
{
	if (t == nullptr) return;
	InOrderTraverse(t->left);
	std::cout << t->data << " ";
	InOrderTraverse(t->right);
}
inline void Tree::PreOrderTraverse(BTree t)
{
	cout << t->data << " ";
	PreOrderTraverse(t->left);
	PreOrderTraverse(t->right);
}
inline void Tree::PostOrderTraverse(BTree t)
{
	PostOrderTraverse(t->left);
	PostOrderTraverse(t->right);
	cout << t->data << " ";
}
inline void Tree::Pre()
{
	cout << "前序遍历为：" << endl;
	PreOrderTraverse(root);
}
inline void Tree::Post()
{
	cout << "后序遍历为：" << endl;
	PostOrderTraverse(root);
}
inline void Tree::In()
{
	cout << "中序遍历为：" << endl;
	InOrderTraverse(root);
}
inline int Tree::Depth()
{
	return getDepth(root);
}
inline int Tree::getDepth(BTree t)
{
	if (t == nullptr)
		return 0;
	return std::max(getDepth(t->left), getDepth(t->right)) + 1;
}
inline void Tree::Create(BTree& t)
{
	char c;
	cin >> c;
	if (c == '#') return;
	else {
		t = new Node(c);
		Create(t->left);
		Create(t->right);
	}
}
