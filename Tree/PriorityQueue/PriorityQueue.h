#pragma once
#include <vector>
using namespace std;
template<class T>
class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(int n);
	~PriorityQueue();
	void push(T t);
	void pop();
	T top();
private:
	vector<T> data(16);
	int size;
	int n;
	void shiftDown(int pos);
	void shiftUp(int pos);
};