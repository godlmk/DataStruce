#pragma once
#include <vector>
#include <cmath>
#include <unordered_map>
using std::cout, std::endl;
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
	//以n为数组大小构建哈希表
	ChainHash(int n);
	//插入一个数据，若已经存在
	void Insert(int x);
	//在表中查找x，若存在就返回它的前一个结点指针，若不存在则返回nullptr
	Node* Find(int x);
	//在表中删除值为x的元素
	bool Delete(int x);
	//打印整个表的所有元素
	void print();
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

inline void ChainHash::print()
{
	printf("除数为%d\n", N);
	auto i{ 0 };
	for (const auto& x : h) {
		printf("第%d个位置的元素：", i++);
		auto p = x.next;
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}
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