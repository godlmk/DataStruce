#pragma once
void MergeSort(int* arr, int l, int r, int* temp) {
	// 当l >= r时可以直接进行比较了，结束递归
	if (l >= r) return;
	int mid = (l + r) >> 1;
	MergeSort(arr, l, mid, temp);
	MergeSort(arr, mid + 1, r, temp);
	int k = 0, i = l, j = mid + 1;
	// 此时mid两边都是有序数组，可以直接用一个数组来将他们呢合并为一个有序数组
	while (i <= mid && j <= r) {
		if (arr[i] <= arr[j]) temp[k++] = arr[i++];
		else temp[k++] = arr[j++];
	}
	while (i <= mid) temp[k++] = arr[i++];
	while (j <= r) temp[k++] = arr[j++];
	// 将有序数组归还给原数组的对应位置
	for (int i = l, j = 0; i <= r; ++i, ++j) arr[i] = temp[j];
}