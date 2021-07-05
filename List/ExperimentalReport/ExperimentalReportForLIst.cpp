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
* ͨ������ʵ�������ṹ��Ľ���
*/
void swapStu(Elemtype& s1, Elemtype& s2) {
	student temp = s1;
	s1 = s2;
	s2 = temp;
}
/*
* ͨ��ָ�뽻�������ṹ��
*/
void swapStu(Elemtype* s1, Elemtype* s2) {
	student temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

/*
* ʹ��ѡ������������������
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
* ���Ա�Ķ���
*/

/*
* ˳���
*/
typedef struct Sqlist {
	Elemtype* elem;
	int length;
};
/*
* ����
*/
typedef struct LNode {
	Elemtype data;
	LNode* next{ nullptr };
}*LinkList;
/*
* ��ʼ�����Ա�
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
* �����Ѵ��ڵ����Ա�
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
* ������Ա�
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
* ��Ϊ�ձ���true�����򷵻�false
*/
bool SequenceListEmpty(const Sqlist& L) {
	return L.length == 0;
}
bool IsLinkListEmpty(const LinkList& L) {
	return L->next == nullptr;
}
/*
* �������Ա��е�Ԫ�ظ���
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
* ��e����L�е�i������Ԫ�ص�ֵ
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
	//��i���������Ȼ���iС��1ʱ
	if (j > i || p == nullptr) return ERROR;
	e = p->data;
	return OK;
}
/*
* ����L�е�1����eֵ��ȵ�Ԫ����L�е�λ��,��δ�ҵ�����0
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
* ��L�е�i��λ�ò�������Ԫ��e������1(�����Ա����г�����Ϣ�Ļ�)
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
* ɾ��L�еĵ�i��Ԫ�أ� L�ĳ��ȼ�1(�����Ա��г�����Ϣ�Ļ�)
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
* �����Ա���б����� ��ÿ��������һ��
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
// �ֱ�ʵ��ͷ�巨��β�巨
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
	// ���ļ��ж������ݵ�stu������
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
	//˳�����֤
	Sqlist QL;
	InitSequenceList(QL);
	for (int i = 0; i < length; ++i)
		SequenceListInsert(QL, i + 1, stu[i]);
	TraversalSequenceList(QL);
	//������֤
	LinkList LL;
	InsertTop(LL, stu, length);
	TraversalLinkList(LL);
	return 0;
}