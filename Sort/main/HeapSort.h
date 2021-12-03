#pragma once
#include <algorithm>

/*
* start����Ҫ����ȷ��λ�õ��±�
* end�ǵ�����Χ������±�
*/
void sink(int arr[], int start, int end)
{
	int tem = arr[start];
	// 2 * i�����������ڵ㣬 2 * i�����������ڵ�
	for (size_t i = 2 * start; i <= end; i *= 2)
	{
		// �ҵ�������������Ľڵ��±�
		if (i < end && arr[i + 1] > arr[i])
			++i;
		// ���start����������������tem����ǰλ�ÿ��Է���tem������ѭ��
		if (tem >= arr[i])
			break;
		// ����ǰλ�õ�ֵ���Ƶ��������
		arr[start] = arr[i];
		start = i;
	}
	arr[start] = tem;
}
void CreateHeap(int arr[], int n)
{
	//�����±�� 1��ʼ�����飬һ���±�Ϊj�Ľڵ�ĸ��ڵ��Ȼ�� j / 2.
	//����ӵ����ڶ��㿪ʼ�³�����Ϊ������һ�㲻��Ҫ�³���
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