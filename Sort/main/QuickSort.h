#pragma once
#include <algorithm>
void  QuickSort(int* arr, int l, int r) {
	if (l >= r) return;

	int i = l - 1, j = r + 1, x = arr[(l + r) >> 1];//������Ҫȡ�м�ֵ����Ȼ�ᳬʱ

	while (i < j) {
		do i++; while (arr[i] < x);
		do j--; while (arr[j] > x);
		if (i < j) std::swap(arr[i], arr[j]);
	}

	QuickSort(arr, l, j);
	QuickSort(arr, j + 1, r);
}