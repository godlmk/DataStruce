#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

/*
��������ĸ��ֺ�
�������������ȷ������
*/

#define OK 1
#define ERROR 0
#define overflow -2
#define MAXSIZE 1000

using namespace std;

typedef int Status;
/*
* �½�һ���ṹ�弴Ϊ���Ա��еĻ���Ԫ�ء�
*/
typedef struct Book {
	string no;
	string name;
	float price{ 0.f };
	bool operator == (const Book& b) const {
		return no == b.no;
	}
};
/*
* sort�����ĵ���������Ϊ�����������������Ϊ���ʱ�����sort�����ǰ�棬
	�������ھ��Ǽ۸�С����ǰ�档
*/
bool comp(Book b1, Book b2) {
	return b1.price < b2.price;
}
typedef  Book ElemType;
/*
����һ�����Ա�Ľṹ�壬���Ա���±��1��ʼ
*/
typedef struct {
	Book* elem;
	int length;
}SqList;
/*
* ��ʼ�����Ա��ڶ��Ͽ���һ�����飬����ĳ���ΪMAXSIZE���������Ա�ĳ�����Ϊ0.
*/
Status InitList(SqList& L) {
	L.elem = new ElemType[MAXSIZE];
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	return OK;
}
/*
* ��ȡ�������Ա��±�Ľṹ�����飬�����������Ӧ����e�С�ͨ��return����״̬��
*/
Status getElement(const SqList& L, int i, ElemType& e) {
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}
/*
* ����ָ�����Ա���ָ���ṹ��Ԫ�ص��±꣬��û���ҵ��򷵻�0.��Ϊ���Ա���±��1��ʼ��
*/
int LocateElem(const SqList& L, Book e) {
	for (int i = 0; i < L.length; ++i)
		if (L.elem[i] == e)
			return i + 1;
	return 0;
}
/*
* �����Ա����±�Ϊi��λ�����һ��Ԫ�أ���iΪlength+1ʱ��ʵ����˼Ϊ����һ���ṹ��Ԫ�ء�
ͨ��return����״̬��
*/
Status InsertList(SqList& L, int i, const ElemType& e) {
	if (i < 1 || i > L.length + 1) return ERROR;
	if (L.length == MAXSIZE) return ERROR;
	for (int j = L.length; j >= i - 1; --j)
		L.elem[j + 1] = L.elem[j];
	L.elem[i - 1] = e;
	++L.length;
	return OK;
}
/*
* ɾ�����Ա��±�Ϊi��Ԫ�أ�i����ЧֵΪ1��length��ͨ��return����״̬��
*/
Status DeleteList(SqList& L, int i) {
	if (i<1 || i > L.length) return ERROR;
	for (int j = i - 1; j < L.length - 1; ++j)
		L.elem[i] = L.elem[i + 1];
	--L.length;
	return OK;
}
int main() {
	Book* books = new Book[100];
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
		file >> books[i].no >> books[i].name >> books[i].price;

		++i;
	}

	file.close();

	int len = i;

	cout << header1 << ' ' << header2 << ' ' << header3 << endl;

	for (int i = 0; i < len; i++)
		cout << books[i].no << ' ' << books[i].name << ' ' << books[i].price << endl;

	SqList list;
	InitList(list);
	for (int i = 1; i <= len; ++i)
		InsertList(list, i, books[i - 1]);
	Book b2;
	sort(list.elem, list.elem + len, comp);
	for (int i = 0; i < len; ++i) {
		getElement(list, i + 1, b2);
		cout << b2.no << " " << b2.name << " " << b2.price << endl;
	}
	cout << LocateElem(list, b2);
	DeleteList(list, 1);
	return 0;
}