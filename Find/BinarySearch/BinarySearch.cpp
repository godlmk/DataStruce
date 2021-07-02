#include <iostream>
#include <random>
using namespace std;
template <typename T>
int Search_binary_iteration(T a[], T target, int len) {
	int l = 0, r = len - 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (a[mid] >= target) r = mid;
		else l = mid + 1;
	}
	if (a[l] != target) l = -1;
	return l;
}
template<typename T>
int Search_binary_recursion(T a[], T target, int l, int r) {
	if (l > r) return -1;
	int mid = l + r >> 1;
	if (a[mid] == target) return mid;
	else if (a[mid] > target) return Search_binary_recursion(a, target, l, mid - 1);
	else return Search_binary_recursion(a, target, mid + 1, r);
}

int main() {
	const int N = 100;
	int* a = new int[N];
	default_random_engine e;
	uniform_int_distribution<int> ra(0, 99);
	for (int i = 0; i < N; ++i) a[i] = ra(e);
	sort(a, a + N);
	for (int i = 0; i < N; ++i) cout << a[i] << endl;
	cout << "The index of 0 is " << Search_binary_recursion(a, a[0], 0, N - 1)
		<< endl;
	return 0;
}