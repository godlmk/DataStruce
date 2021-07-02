#pragma once
void InsertSort(int* arr, int len) {
	for (int i = 2; i < len; ++i)
		if (arr[i] < arr[i - 1]) {
			auto tem = arr[i];
			arr[i] = arr[i - 1];
			int j;
			for (j = i - 2; arr[j] > tem; --j)
				arr[j + 1] = arr[j];
			arr[j + 1] = tem;
		}
}