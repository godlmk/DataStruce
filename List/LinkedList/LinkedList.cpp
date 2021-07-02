#include <iostream>
#include <fstream>
#include <string>
#include <array>
#define OK 1
#define ERROR 0
#define overflow -2
typedef int Status;

using namespace std;

// �ṹ�嶨�壬���ڽṹ���н������������
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

// ����������ÿ���ڵ�Ľṹ������ΪLNode��LinkList
typedef struct LNode
{
	ElemType data;
	LNode* next{ nullptr };
}*LinkList;

// ��ʼ������,�½�ͷ�ڵ㣬��������next��Ϊnull��
Status InitList(LinkList& L) {
	L = new LNode;
	L->next = nullptr;
	return OK;
}

/*ͨ������i�ҵ������еĵ�i��Ԫ�أ�j��ʼ��Ϊ1����iС��1�Ļ��� j > i ���ش����� i ��������ĳ��ȣ���
	���ҵ��������Ҳ�޷��ҵ�����ʱ p �Ѿ������������λ�õ�nextָ���λ�ã�nullptr�������ش���
*/
Status GetElem(LinkList L, int i, ElemType& e) {
	//ʹ��pָ������ĵ�һ��Ԫ��
	LNode* p = L->next;
	//��ʼ��jΪ1�� ��p��ʼ��ָ�������λ�á�
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
* �������������ݵ�ֵ����e�Ľڵ��ָ�롣��δ�ҵ��᷵��nullptr��
*/
LNode* LocateElem(LinkList L, ElemType e) {
	LNode* p = L->next;
	while (p && p->data != e) p = p->next;
	return p;
}

/*
* �½�һ���ڵ������ݵ���e�� �������嵽����ĵ�i��λ���ϡ�i�ĺϷ�λ��Ϊ1 ~ ������+1
*/
Status ListInsert(LinkList& L, int i, ElemType e) {
	//ʹ��pָ�������ͷ�ڵ�
	LNode* p = L;
	//��ʼ��jΪ0�� ��p��ʱδָ���κ�Ԫ�ء�
	auto j{ 0 };
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	/* ��pΪ���һ��Ԫ�صĵ�ַ����iΪ������+1ʱ����ʱ���᷵�ش���
	* ��iΪ1������Ҫͨ��ͷ�ڵ�����ӵ�һ��Ԫ�أ�
	  ��iΪ������ + 1����p��Ҫָ�����һ��Ԫ����������һ���½ڵ㡣
	*/
	if (!p || j > i - 1) return ERROR;
	LNode* n = new LNode;
	n->data = e;
	n->next = p->next;
	p->next = n;
	return OK;
}

/*
* ɾ�������i��λ���ϵĽڵ㣬i�ĺϷ�λ��Ϊ1 ~ ����ĳ��ȣ�
*/
Status ListDelete(LinkList L, int i) {
	// ʹ��pָ�������ͷ�ڵ�
	LNode* p = L->next;
	//��ʼ��jΪ0�� ��p��ʱ��Ϊָ���κ�Ԫ�ء�
	auto j{ 0 };
	// ��pδ���ﵹ���ڶ���Ԫ�أ���δ����i��ǰһ��λ�ã�����ѭ����
	while (p->next && j < i - 1) {
		p = p->next;
		++j;
	}
	/*
	 ����pΪ���һ��Ԫ�� ���� i < 1���ش���
	 ��iΪ1ʱ��pָ��ͷ�ڵ㣬��ʱ��Ҫͨ��ͷ�ڵ���ɾ�������һ��Ԫ�أ�
	 ��iΪ������ʱ��pӦָ�����ڶ����ڵ�
	*/
	if (!(p->next) || j > i - 1) return ERROR;
	LNode* t = p->next;
	p->next = t->next;
	delete t;
	return OK;
}

// ��������

int ListGetLength(const LinkList& L) {
	auto p{ L };
	auto len{ -1 };
	while (p) {
		++len;
		p = p->next;
	}
	return len;
}

// �����п�
bool IsEmpty(const LinkList& L) {
	return L->next == nullptr;
}

// ǰ�巨
void CreatLink_H(LinkList& L, array<ElemType, 100> Data, int n) {
	L = new LNode;
	for (int i = 0; i < n; ++i) {
		auto p = new LNode;
		p->data = Data[i];
		p->next = L->next;
		L->next = p;
	}
}

// ��巨
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
// ���������������
void ErgodicList(const LinkList& L) {
	auto p{ L->next };
	while (p) {
		cout << p->data.id << " " << p->data.name << " " << p->data.price << endl;
		p = p->next;
	}
}
/*
* �õݹ��ѯ�����е����۸�
*/
float Max(const LinkList& L) {
	if (L->next == nullptr) return L->data.price;
	return max(L->data.price, Max(L->next));
}

/*
* �õݹ�������Ľ�����
*/
int getNumbersRecursion(const LinkList& L) {
	if (L == nullptr) return 0;
	return getNumbersRecursion(L->next) + 1;
}
//�õݹ������е�Ԫ�ص�ƽ��ֵ
double getAverageRecursion(const LinkList& L, int n) {
	if (L->next == nullptr)return L->data.price;
	double res = getAverageRecursion(L->next, n - 1);
	return (res * (n - 1) + L->data.price) / n;
}
int main() {
	//���ļ�����������
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
	//��ʼ������ͨ����巨
	CreatLink_T(L, books, len);
	ErgodicList(L);
	Book b1; GetElem(L, 10, b1);
	cout << b1.id << " " << b1.name << " " << b1.price << endl;
	cout << "The max price is : " << Max(L) << endl;
	cout << "The numbers is : " << getNumbersRecursion(L) << endl;
	cout << "The average is : " << getAverageRecursion(L, len) << endl;
	return 0;
}