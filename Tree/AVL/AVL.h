#pragma once
class AVL
{
public:
	AVL();
	~AVL();

private:
	struct Node
	{
		char data;
		Node* left, * right;
		int height;
		Node(char c)
		{
			data = c;
			left = right = nullptr;
			height = 0;
		}
	};
	Node* root;
};

AVL::AVL()
{
}

AVL::~AVL()
{
}