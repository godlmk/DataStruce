#pragma once
#include <algorithm>
void bubbleSortNormal(int* arr, int len) {
	for (int i = 0; i < len - 1; ++i)
		for (int j = 0; j < len - i - 1; ++j) {
			if (arr[j] > arr[j + 1])
				std::swap(arr[j], arr[j + 1]);
		}
}
void bubbleSortOptimize1(int* arr, int len) {
	for (int i = 0; i < len - 1; ++i) {
		bool isChange = false;
		for (int j = 0; j < len - i - 1; ++j)
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				isChange = true;
			}
		if (!isChange) break;
	}
}
void bublleSortOptimize2(int* arr, int len) {
	auto exchange{ len }, bound = 0;
	while (exchange) {
		bound = exchange;
		exchange = 0;
		for (int j = 0; j < bound - 1; ++j)
			if (arr[j] > arr[j + 1]) {
				std::swap(arr[j], arr[j + 1]);
				exchange = j + 1;
			}
	}
}
