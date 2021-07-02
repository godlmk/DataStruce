#pragma once
#include <string>
#include <ctime>
#include "SelectionSort.h"
#include "BubbleSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "InsertSort.h"
using namespace std;
int* genderOrderArray(int n) {
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) arr[i] = i;
	return arr;
}
int* genderRandomArray(int n) {
	int* arr = new int[n];
	for (int i = 0; i < n; ++i) arr[i] = rand() % n;
	return arr;
}
int* copyArray(int* arr, int n) {
	int* ans = new int[n];
	for (int i = 0; i < n; ++i) ans[i] = arr[i];
	return ans;
}
bool testSort(int* arr, int n) {
	for (int i = 0; i < n - 1; ++i)
		if (arr[i] > arr[i + 1]) return false;
	return true;
}
void sortTime(int* arr, int n, string sortName) {
	clock_t startTime = clock();
	if (sortName == "SelectionSort") selectSort(arr, n);
	else if (sortName == "BubbleSort") bubbleSortNormal(arr, n);
	else if (sortName == "QuickSort") QuickSort(arr, 0, n - 1);
	else if (sortName == "MergeSort") { int* temp = new int[n]; MergeSort(arr, 0, n - 1, temp); }
	else if (sortName == "InsertSort") InsertSort(arr, n);
	cout << sortName << ": 是否排序成功： " << testSort(arr, n);
	auto endTime = clock();
	cout << "   排序需要的时间为："
		<< static_cast<double>(endTime - startTime) / CLOCKS_PER_SEC << " s" << endl;
}