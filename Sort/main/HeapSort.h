#pragma once
#include <algorithm>

/*
* start是需要重新确定位置的下标
* end是调整范围的最大下标
*/
void sink(int arr[], int start, int end)
{
	int tem = arr[start];
	// 2 * i是左子树根节点， 2 * i是右子树根节点
	for (size_t i = 2 * start; i <= end; i *= 2)
	{
		// 找到左右子树更大的节点下标
		if (i < end && arr[i + 1] > arr[i])
			++i;
		// 如果start的自由子树均不比tem大，则当前位置可以放置tem，结束循环
		if (tem >= arr[i])
			break;
		// 将当前位置的值复制到父结点上
		arr[start] = arr[i];
		start = i;
	}
	arr[start] = tem;
}
void CreateHeap(int arr[], int n)
{
	//对于下标从 1开始的数组，一个下表为j的节点的父节点必然是 j / 2.
	//这里从倒数第二层开始下沉，因为倒数第一层不需要下沉。
	for (size_t i = n / 2; i > 0; --i)
	{
		sink(arr, i, n);
	}
}

void HeapSort(int arr[], int n)
{
	CreateHeap(arr, n - 1);

	for (size_t i = n; i > 1; --i)
	{
		std::swap(arr[1], arr[i]);
		sink(arr, 1, i - 1);
	}
	
}