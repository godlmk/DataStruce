#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

/*
定义所需的各种宏
赋予给个整形以确切意义
*/

#define OK 1
#define ERROR 0
#define overflow -2
#define MAXSIZE 1000

using namespace std;

typedef int Status;
/*
* 新建一个结构体即为线性表中的基本元素。
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
* sort函数的第三个参数为函数，这个函数返回为真的时候就是sort排序的前面，
	例如现在就是价格小的在前面。
*/
bool comp(Book b1, Book b2) {
	return b1.price < b2.price;
}
typedef  Book ElemType;
/*
定义一个线性表的结构体，线性表的下标从1开始
*/
typedef struct {
	Book* elem;
	int length;
}SqList;
/*
* 初始化线性表，在堆上开辟一个数组，数组的长度为MAXSIZE，并将线性表的长度置为0.
*/
Status InitList(SqList& L) {
	L.elem = new ElemType[MAXSIZE];
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	return OK;
}
/*
* 获取给定线性表下标的结构体数组，并将结果存入应引用e中。通过return返回状态码
*/
Status getElement(const SqList& L, int i, ElemType& e) {
	if (i < 1 || i > L.length) return ERROR;
	e = L.elem[i - 1];
	return OK;
}
/*
* 返回指定线性表中指定结构体元素的下标，若没有找到则返回0.因为线性表的下标从1开始。
*/
int LocateElem(const SqList& L, Book e) {
	for (int i = 0; i < L.length; ++i)
		if (L.elem[i] == e)
			return i + 1;
	return 0;
}
/*
* 在线性表中下标为i的位置添加一个元素，当i为length+1时，实际意思为新增一个结构体元素。
通过return返回状态码
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
* 删除线性表下标为i的元素，i的有效值为1到length。通过return返回状态码
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