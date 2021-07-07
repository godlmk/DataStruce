#pragma once
#include <vector>
#include <cmath>
#include <unordered_map>
class ChainHash
{
private:
	struct Node
	{
		int data{ 0 };
		Node* next;
		Node() :data{ 0 }, next{ nullptr } {}
		Node(int e) :data{ e }, next{ nullptr } {}
	};
public:
	ChainHash();
	~ChainHash();
	ChainHash(int n);
	void Insert(int x);
	Node* Find(int x);
	bool Delete(int x);
private:
	std::vector<Node> h;
	int N = 2;
	bool IsPrime(int n);
};

ChainHash::ChainHash() :N(7)
{
	h.resize(10);
}
ChainHash::ChainHash(int n) {
	h.resize(n);
	int i;
	for (i = n; !IsPrime(i); --i);
	N = i;
}
void ChainHash::Insert(int x) {
	if (auto p = Find(x))
		return;
	auto index = (x % N + N) % N;
	auto p = &h[index], t = new Node(x);
	t->next = p->next;
	p->next = t;
}
ChainHash::Node* ChainHash::Find(int x) {
	auto index = (x % N + N) % N;
	auto slow = &h[index], fast = h[index].next;
	while (fast != nullptr && fast->data != x) {
		slow = fast;
		fast = fast->next;
	}
	if (fast) return slow;
	else return fast;
}
bool ChainHash::Delete(int x) {
	if (auto p = Find(x)) {
		auto temp = p->next;
		p->next = p->next->next;
		delete temp;
		return true;
	}
	return false;
}

bool ChainHash::IsPrime(int n)
{
	for (int i = 2; i <= std::sqrt(n); ++i)
		if (n % i == 0) return false;
	return true;
}

ChainHash::~ChainHash()
{
}