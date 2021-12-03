#pragma once
#include <algorithm>
void  QuickSort(int* arr, int l, int r) {
	if (l >= r) return;

	int i = l, j = r;//������Ҫȡ�м�ֵ����Ȼ�ᳬʱ

	while (i < j) {
		while (j > i && arr[j] >= arr[l]) --j;
		while (i < j && arr[i] <= arr[l]) ++i;
		std::swap(arr[i], arr[j]);
	}
	std::swap(arr[i], arr[l]);

	QuickSort(arr, l, j);
	QuickSort(arr, j + 1, r);
}