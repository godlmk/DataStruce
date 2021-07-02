#pragma once
class SqStack {
public:
	SqStack(int size);
	bool Push(int e);
	bool Pop(int& e);
	bool Peek(int& e);
private:
	int* data;
	int top, stackSize;
	bool isEmpty();
	bool isFull();
};