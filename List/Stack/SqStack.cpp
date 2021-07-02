#include <iostream>
#include <fstream>
#include <string>
#include <array>

#include "SqStackH.h"
#define OK 1
#define ERROR 0
#define overflow -2
#define MAXSIZE 100
typedef int Status;

using namespace std;

//struct SqStack
//{
//	int top, stackSize;
//	int* data;
//};
//
//typedef int ElemType;
//
///*
//* 构造一个空栈
//*/
//
//Status InitStack(SqStack& s) {
//	s.data = new int(MAXSIZE);
//	if (!s.data) return ERROR;
//	s.top = 0;
//	s.stackSize = MAXSIZE;
//	return OK;
//}
//
//Status Push(SqStack& S, ElemType e) {
//	if (S.top == S.stackSize) return ERROR;
//	S.data[S.top++] = e;
//	return OK;
//}
//
//Status Pop(SqStack& S, ElemType& e) {
//	if (S.top == 0)return ERROR;
//	e = S.data[--S.top];
//	return OK;
//}
//
//Status Peek(SqStack& S, ElemType& e) {
//	if (S.top == 0) return ERROR;
//	e = S.data[S.top - 1];
//	return OK;
//}
int main() {
	SqStack stk(100);
	for (int i = 0; i < 100; ++i) {
		stk.Push(i);
		int temp;
		stk.Pop(temp);
		cout << temp << endl;
	}
	int t;
	if (stk.Pop(t))
		cout << "still have elem" << endl;
	else cout << "have no elem" << endl;
	return 0;
}