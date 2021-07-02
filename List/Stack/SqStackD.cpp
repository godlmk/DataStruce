#include "SqStackH.h"

SqStack::SqStack(int size)
{
	data = new int[size];
	stackSize = size;
	top = 0;
}

bool SqStack::isEmpty() { return top == 0; }

bool SqStack::isFull() { return top == stackSize; }

bool SqStack::Push(int e) {
	if (isFull()) return false;
	data[top++] = e;
	return true;
}

bool SqStack::Pop(int& e) {
	if (isEmpty()) return false;
	e = data[--top];
	return true;
}

bool SqStack::Peek(int& e) {
	if (isEmpty()) return false;
	e = data[top - 1];
	return true;
}