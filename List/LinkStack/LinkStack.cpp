#include <iostream>
#define OK 1
#define ERROR 0
#define overflow -2
typedef int Status;
typedef int ElemType;
using namespace std;
typedef struct StackNode {
	ElemType data;
	StackNode* next;
}*LinkStack;

Status InitStack(LinkStack& S) {
	S = nullptr;
	return OK;
}

Status Push(LinkStack& S, ElemType e) {
	StackNode* p = new StackNode;
	p->data = e;
	p->next = S;
	S = p;
	return OK;
}

Status Pop(LinkStack& S, ElemType& e) {
	if (S == nullptr) return ERROR;
	e = S->data;
	auto p = S;
	S = S->next;
	delete p;
	return OK;
}

Status Peek(LinkStack& S, ElemType& e) {
	if (S == nullptr) return ERROR;
	e = S->data;
	return OK;
}

int main() {
	LinkStack s;
	for (int i = 0; i < 100; ++i)
		Push(s, i);
	for (int i = 0; i < 101; ++i) {
		int t;
		if (Pop(s, t) > 0)
			cout << t << endl;
		else
			cout << "Empty" << endl;
	}
	return 0;
}