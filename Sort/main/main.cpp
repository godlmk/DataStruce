#include <iostream>
#include"SortTest.h"
using namespace std;

const long N = 1000000;
int main() {
	int* arr1 = genderRandomArray(N);
	int* arr2 = copyArray(arr1, N);
	/*int* arr3 = copyArray(arr1, N);
	int* arr4 = copyArray(arr1, N);
	int* arr5 = copyArray(arr1, N);*/
	sortTime(arr1, N, "HeapSort");
	delete[]arr1;
	/*sortTime(arr2, N, "MergeSort");
	delete[]arr2;*/
	/*sortTime(arr3, N, "InsertSort");
	delete[]arr3;
	sortTime(arr4, N, "SelectionSort");
	delete[]arr4;
	sortTime(arr5, N, "BubbleSort");
	delete[]arr5;*/
	return 0;
}