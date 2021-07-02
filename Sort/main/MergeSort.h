#pragma once
void MergeSort(int* arr, int l, int r, int* temp) {
	if (l >= r) return;
	int mid = (l + r) >> 1;
	MergeSort(arr, l, mid, temp);
	MergeSort(arr, mid + 1, r, temp);
	int k = 0, i = l, j = mid + 1;
	while (i <= mid && j <= r) {
		if (arr[i] <= arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}
	while (i <= mid) temp[k++] = arr[i++];
	while (j <= r) temp[k++] = arr[j++];
	for (int i = l, j = 0; i <= r; ++i, ++j) arr[i] = temp[j];
}