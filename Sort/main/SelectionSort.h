#pragma once
#include <algorithm>
void selectSort(int* arr, int len) {
	for (int i = 0; i < len; ++i) {
		int minIndex{ i };
		for (int j = i + 1; j < len; ++j)
			if (arr[j] < arr[minIndex])
				minIndex = j;
		if (minIndex != i)
			std::swap(arr[i], arr[minIndex]);
	}
}
