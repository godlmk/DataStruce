#include <iostream>
#include <fstream>
#include <string>
#include <array>
#define OK 1
#define ERROR 0
#define overflow -2
typedef int Status;

using namespace std;

// 结构体定义，并在结构体中进行运算符重载
struct Book
{
	string id, name;
	float price{ 0.f };
	bool operator == (const Book& b)const {
		return b.id == id;
	}
	bool operator != (const Book& b)const {
		return b.id != id;
	}
};
typedef Book ElemType;

// 定义链表中每个节点的结构，命名为LNode和LinkList
typedef struct LNode
{
	ElemType data;
	LNode* next{ nullptr };
}*LinkList;

// 初始化链表,新建头节点，并将他的next置为null；
Status InitList(LinkList& L) {
	L = new LNode;
	L->next = nullptr;
	return OK;
}

/*通过数字i找到链表中的第i个元素，j初始化为1，若i小于1的话则 j > i 返回错误，若 i 大于链表的长度，则
	则找到链表最后也无法找到，此时 p 已经到达链表最后位置的next指向的位置（nullptr），返回错误。
*/
Status GetElem(LinkList L, int i, ElemType& e) {
	//使得p指向链表的第一个元素
	LNode* p = L->next;
	//初始化j为1， 即p初始化指向的链表位置。
	auto j{ 1 };
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	e = p->data;
	return OK;
}

/*
* 返回链表中数据的值等于e的节点的指针。若未找到会返回nullptr；
*/
LNode* LocateElem(LinkList L, ElemType e) {
	LNode* p = L->next;
	while (p && p->data != e) p = p->next;
	return p;
}

/*
* 新建一个节点其数据等于e， 并将他插到链表的第i个位置上。i的合法位置为1 ~ 链表长度+1
*/
Status ListInsert(LinkList& L, int i, ElemType e) {
	//使得p指向链表的头节点
	LNode* p = L;
	//初始化j为0， 即p此时未指向任何元素。
	auto j{ 0 };
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	/* 若p为最后一个元素的地址，且i为链表长度+1时，此时不会返回错误。
	* 若i为1，则需要通过头节点来添加第一个元素，
	  若i为链表长度 + 1，则p需要指向最后一个元素在最后添加一个新节点。
	*/
	if (!p || j > i - 1) return ERROR;
	LNode* n = new LNode;
	n->data = e;
	n->next = p->next;
	p->next = n;
	return OK;
}

/*
* 删除链表第i个位置上的节点，i的合法位置为1 ~ 链表的长度；
*/
Status ListDelete(LinkList L, int i) {
	// 使得p指向链表的头节点
	LNode* p = L->next;
	//初始化j为0， 即p此时还为指向任何元素。
	auto j{ 0 };
	// 若p未到达倒数第二个元素，且未到达i的前一个位置，继续循环。
	while (p->next && j < i - 1) {
		p = p->next;
		++j;
	}
	/*
	 若，p为最后一个元素 或者 i < 1返回错误。
	 当i为1时，p指向头节点，此时需要通过头节点来删除链表第一个元素，
	 当i为链表长度时，p应指向倒数第二个节点
	*/
	if (!(p->next) || j > i - 1) return ERROR;
	LNode* t = p->next;
	p->next = t->next;
	delete t;
	return OK;
}

// 求链表长度

int ListGetLength(const LinkList& L) {
	auto p{ L };
	auto len{ -1 };
	while (p) {
		++len;
		p = p->next;
	}
	return len;
}

// 链表判空
bool IsEmpty(const LinkList& L) {
	return L->next == nullptr;
}

// 前插法
void CreatLink_H(LinkList& L, array<ElemType, 100> Data, int n) {
	L = new LNode;
	for (int i = 0; i < n; ++i) {
		auto p = new LNode;
		p->data = Data[i];
		p->next = L->next;
		L->next = p;
	}
}

// 后插法
void CreatLink_T(LinkList& L, array<ElemType, 100> Data, int n) {
	L = new LNode;
	LNode* tail{ L };
	for (int i = 0; i < n; ++i) {
		auto p = new LNode;
		p->data = Data[i];
		tail->next = p;
		tail = p;
	}
}
// 遍历输出整个链表
void ErgodicList(const LinkList& L) {
	auto p{ L->next };
	while (p) {
		cout << p->data.id << " " << p->data.name << " " << p->data.price << endl;
		p = p->next;
	}
}
/*
* 用递归查询链表中的最大价格
*/
float Max(const LinkList& L) {
	if (L->next == nullptr) return L->data.price;
	return max(L->data.price, Max(L->next));
}

/*
* 用递归求链表的结点个数
*/
int getNumbersRecursion(const LinkList& L) {
	if (L == nullptr) return 0;
	return getNumbersRecursion(L->next) + 1;
}
//用递归求所有的元素的平均值
double getAverageRecursion(const LinkList& L, int n) {
	if (L->next == nullptr)return L->data.price;
	double res = getAverageRecursion(L->next, n - 1);
	return (res * (n - 1) + L->data.price) / n;
}
int main() {
	//将文件读入数组中
	array<ElemType, 100> books;
	string header1, header2, header3;

	fstream file;

	file.open("D:\\Book.txt");

	if (!file)

	{
		cout << "read file error";

		return 1;
	}

	else

		cout << "read file ok" << endl;

	int i = 0;

	file >> header1 >> header2 >> header3;

	while (!file.eof()) {
		file >> books[i].id >> books[i].name >> books[i].price;

		++i;
	}

	file.close();

	int len = i;

	cout << header1 << ' ' << header2 << ' ' << header3 << endl;

	LinkList L = nullptr;
	InitList(L);
	//初始化链表，通过后插法
	CreatLink_T(L, books, len);
	ErgodicList(L);
	Book b1; GetElem(L, 10, b1);
	cout << b1.id << " " << b1.name << " " << b1.price << endl;
	cout << "The max price is : " << Max(L) << endl;
	cout << "The numbers is : " << getNumbersRecursion(L) << endl;
	cout << "The average is : " << getAverageRecursion(L, len) << endl;
	return 0;
}