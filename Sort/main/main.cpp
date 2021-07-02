#include <iostream>
#include"SortTest.h"
using namespace std;

const int N = 100000;
int main() {
	int* arr1 = genderRandomArray(N);
	int* arr2 = copyArray(arr1, N);
	int* arr3 = copyArray(arr1, N);
	int* arr4 = copyArray(arr1, N);
	int* arr5 = copyArray(arr1, N);
	sortTime(arr1, N, "QuickSort");
	sortTime(arr2, N, "MergeSort");
	sortTime(arr3, N, "InsertSort");
	sortTime(arr4, N, "SelectionSort");
	sortTime(arr5, N, "BubbleSort");
	delete[]arr1;
	delete[]arr2;
	delete[]arr3;
	delete[]arr4;
	delete[]arr5;
	return 0;
}