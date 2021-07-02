#include <iostream>

using namespace std;
typedef int QElemType;
typedef struct QNode {
	QElemType data;
	QNode* next;
}*QueuePtr;
struct LinkQueue
{
	QueuePtr front, rear;
};
bool init(LinkQueue& L) {
	L.front = L.rear = new QNode;
	L.front->next = nullptr;
}
bool isEmpty(LinkQueue L) {
	return L.front == L.rear;
}
bool EnQueue(LinkQueue& L, QElemType e) {
	auto p = new QNode;
	p->data = e;
	L.rear->next = p;
	p->next = nullptr;
	L.rear = p;
	return true;
}
bool DeQueue(LinkQueue& L, QElemType& e) {
	if (isEmpty(L)) return false;
	auto p = L.front->next;
	e = p->data;
	L.front = p->next;
	if (p == L.rear)
		L.rear = L.front;
	delete p;
	return true;
}
bool GetHead(LinkQueue L, QElemType& e) {
	if (isEmpty(L)) return false;
	e = L.front->next->data;
	return true;
}
int main() {
	return 0;
}