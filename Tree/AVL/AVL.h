#pragma once
#include <algorithm>
class AVL
{
private:
	struct Node
	{
		int data;
		Node* left, * right;
		int height;
		Node(int c)
		{
			data = c;
			left = right = nullptr;
			height = 0;
		}
	};
	Node* root{ nullptr };
public:
	AVL();
	~AVL();
	Node* LL(Node* t);
	Node* RR(Node* t);
	Node* LR(Node* t);
	Node* RL(Node* t);
	int height(Node* t);
	Node* Insert(Node* t, int e);
	void Insert(int e);
	void PreOrder(Node* t);
	void PreOrderTraverse();
	void InorderTraverse(Node* t);
	void InorderTraverse();
};

AVL::AVL()
{
	root = nullptr;
}
int AVL::height(Node* t)
{
	return t == nullptr ? -1 : t->height;
}

void AVL::PreOrder(Node* t) {
	if (t) {
		std::cout << t->data << "  ";
		PreOrder(t->left);
		PreOrder(t->right);
	}
	return;
}
void AVL::PreOrderTraverse() {
	std::cout << " 先序遍历为：" << std::endl;
	PreOrder(root);
}
inline void AVL::InorderTraverse(Node* t)
{
	if (!t) return;
	InorderTraverse(t->left);
	std::cout << t->data << " ";
	InorderTraverse(t->right);
}
inline void AVL::InorderTraverse()
{
	std::cout << "\n中序遍历为：" << std::endl;
	InorderTraverse(root);
}
AVL::Node* AVL::LL(Node* t) {
	auto p = t->left;
	t->left = p->right;
	p->right = t;
	t->height = std::max(height(t->left), height(t->right)) + 1;
	p->height = std::max(height(p->left), height(p->right)) + 1;
	return p;
}

AVL::Node* AVL::RR(Node* t) {
	auto p = t->right;
	t->right = p->left;
	p->left = t;
	t->height = std::max(height(t->left), height(t->right)) + 1;
	p->height = std::max(height(p->left), height(p->right)) + 1;
	return p;
}
AVL::Node* AVL::LR(Node* t) {
	t->left = RR(t->left);
	return LL(t);
}
AVL::Node* AVL::RL(Node* t) {
	t->right = LL(t->right);
	return RR(t);
}
AVL::Node* AVL::Insert(Node* t, int e) {
	if (!t) {
		t = new Node(e);
		return t;
	}
	if (e < t->data) {
		t->left = Insert(t->left, e);
		if (height(t->left) - height(t->right) == 2)
			if (e < t->left->data)
				t = LL(t);
			else t = LR(t);
	}
	else if (e > t->data) {
		t->right = Insert(t->right, e);
		if (height(t->left) - height(t->right) == -2)
			if (e > t->right->data)
				t = RR(t);
			else t = RL(t);
	}
	t->height = std::max(height(t->left), height(t->right)) + 1;
	return t;
}

void AVL::Insert(int e)
{
	root = Insert(root, e);
}

AVL::~AVL()
{
	delete root;
}