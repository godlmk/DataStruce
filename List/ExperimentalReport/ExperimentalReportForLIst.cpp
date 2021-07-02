#include <iostream>
#include <fstream>
#include <string>

#define OK 1
#define ERROR 0
#define overflow -2
#define MAXSIZE 100

typedef int Status;

using namespace std;

struct student {
	string name, studentNumber;
	int sore{ 0 };
};
typedef student Elemtype;

/*
* 通过引用实现两个结构体的交换
*/
void swapStu(Elemtype& s1, Elemtype& s2) {
	student temp = s1;
	s1 = s2;
	s2 = temp;
}
/*
* 通过指针交换两个结构体
*/
void swapStu(Elemtype* s1, Elemtype* s2) {
	student temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

/*
* 使用选择排序对数组进行排序
*/
void selectSort(Elemtype arr[], int n) {
	for (int i = 0; i < n; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < n; ++j) {
			if (arr[j].sore < arr[i].sore)
				minIndex = j;
		}
		swapStu(arr[minIndex], arr[i]);
	}
}

/*
* 线性表的定义
*/

/*
* 顺序表
*/
typedef struct Sqlist {
	Elemtype* elem;
	int length;
};
/*
* 链表
*/
typedef struct LNode {
	Elemtype data;
	LNode* next{ nullptr };
}*LinkList;
/*
* 初始化线性表
*/
Status InitSequenceList(Sqlist& L) {
	L.elem = new Elemtype[MAXSIZE];
	if (!L.elem) return ERROR;
	L.length = 0;
	return OK;
}
Status InitLinkList(LinkList& L) {
	L = new LNode;
	if (L == nullptr) return ERROR;
	L->next = nullptr;
	return OK;
}
/*
* 销毁已存在的线性表
*/
Status DestroySequenceList(Sqlist& L) {
	delete[] L.elem;
	L.length = 0;
	return OK;
}

void DestroyLinkList(LinkList& L) {
	while (L) {
		LNode* temp = L->next;
		delete L;
		L = temp;
	}
}

/*
* 清空线性表
*/
void ClearSequenceList(Sqlist& L) {
	L.length = 0;
}
void ClearLinkList(LinkList& L) {
	LNode* second = L->next;
	while (second) {
		LNode* temp = second->next;
		delete second;
		second = temp;
	}
	L->next = nullptr;
}
/*
* 若为空表返回true，否则返回false
*/
bool SequenceListEmpty(const Sqlist& L) {
	return L.length == 0;
}
bool IsLinkListEmpty(const LinkList& L) {
	return L->next == nullptr;
}
/*
* 返回线性表中的元素个数
*/
int SequenceListLength(const Sqlist& L) {
	return L.length;
}

int LinkListLength(LinkList L) {
	int len = 0;
	while (L) {
		++len;
		L = L->next;
	}
	return len;
}
/*
* 用e返回L中第i个数据元素的值
*/
Status GetSequenceElem(const Sqlist& L, int i, Elemtype& e) {
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}

Status GetLinkElem(const LinkList& L, int i, Elemtype& e) {
	int j = 1;
	LNode* p = L->next;
	while (j < i && p) {
		++j;
		p = p->next;
	}
	//当i大于链表长度或者i小于1时
	if (j > i || p == nullptr) return ERROR;
	e = p->data;
	return OK;
}
/*
* 返回L中第1个和e值相等的元素在L中的位置,若未找到返回0
*/
int LocateSequenceElem(const Sqlist& L, Elemtype e) {
	for (int i = 0; i < L.length; ++i)
		if (L.elem[i].studentNumber == e.studentNumber)
			return i + 1;
	return 0;
}

int LocateLinkElem(const LinkList& L, Elemtype e) {
	int j = 1;
	LNode* p = L->next;
	while (p) {
		if (p->data.studentNumber == e.studentNumber)
			return j;
		++j;
		p = p->next;
	}
	return 0;
}
/*
* 在L中第i个位置插入数据元素e，表长加1(若线性表中有长度信息的话)
*/
Status SequenceListInsert(Sqlist& L, int i, Elemtype e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length == MAXSIZE) return ERROR;
	for (int j = L.length - 1; j >= i - 1; --j) {
		L.elem[j + 1] = L.elem[j];
	}
	L.elem[i - 1] = e;
	++L.length;
	return OK;
}

Status LinkListInsert(LinkList& L, int i, Elemtype e) {
	int j = 0;
	LNode* p = L;
	while (j < i - 1 && p) {
		++j;
		p = p->next;
	}
	if (j > i - 1 || !p) return ERROR;
	LNode* temp = new LNode;
	temp->data = e;
	temp->next = p->next;
	p->next = temp;
	return OK;
}
/*
* 删除L中的第i个元素， L的长度减1(若线性表有长度信息的话)
*/
Status SequenceListDelete(Sqlist& L, int i) {
	if (i < 1 || i > L.length) return ERROR;
	for (int j = i - 1; j < L.length - 1; ++j)
		L.elem[j] = L.elem[j + 1];
	--L.length;
	return OK;
}
Status LinkListDelete(LinkList& L, int i) {
	int j = 0;
	LNode* p = L;
	while (j < i - 1 && p->next) {
		++j;
		p = p->next;
	}
	if (j > i - 1 || !(p->next)) return ERROR;
	LNode* temp = p->next;
	p->next = temp->next;
	delete temp;
	return OK;
}
/*
* 对线性表进行遍历， 对每个结点访问一次
*/
void TraversalSequenceList(const Sqlist& L) {
	cout << "TraversalSequence begin:" << endl;
	for (int i = 0; i < L.length; ++i)
		cout << L.elem[i].studentNumber << " " << L.elem[i].name << " " << L.elem[i].sore << endl;
	cout << "Sequence Traversal ends" << endl;
}
void TraversalLinkList(const LinkList& L) {
	LNode* p = L->next;
	cout << "TraversalLinkList Begin:" << endl;
	while (p) {
		cout << p->data.studentNumber << " " << p->data.name << " " << p->data.sore << endl;
		p = p->next;
	}
	cout << "LinkList Traversal ends" << endl;
}
// 分别实现头插法和尾插法
void InsertTop(LinkList& L, Elemtype s[], int n) {
	L = new LNode;
	L->next = nullptr;
	for (int i = 0; i < n; ++i) {
		LNode* e = new LNode;
		e->data = s[i];
		e->next = L->next;
		L->next = e;
	}
}
void InsertTail(LinkList& L, Elemtype s[], int n) {
	L = new LNode;
	L->next = nullptr;
	LNode* p = L;
	for (int i = 0; i < n; ++i) {
		LNode* e = new LNode;
		e->data = s[i];
		e->next = p->next;
		p->next = e;
		p = e;
	}
}
int main() {
	// 从文件中读入数据到stu数组中
	Elemtype* stu = new Elemtype[20];
	string header1, header2, header3;
	fstream file;
	file.open("D:/Student.txt");
	if (!file) {
		cout << "Open Error";
		exit(1);
	}
	file >> header1 >> header2 >> header3;
	int i{ 0 };
	while (!file.eof()) {
		file >> stu[i].studentNumber >> stu[i].name >> stu[i].sore;
		++i;
	}
	file.close();
	int length = i;
	cout << header1 << " " << header2 << " " << header3 << endl;

	selectSort(stu, length);
	//顺序表验证
	Sqlist QL;
	InitSequenceList(QL);
	for (int i = 0; i < length; ++i)
		SequenceListInsert(QL, i + 1, stu[i]);
	TraversalSequenceList(QL);
	//链表验证
	LinkList LL;
	InsertTop(LL, stu, length);
	TraversalLinkList(LL);
	return 0;
}