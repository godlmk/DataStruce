#include <iostream>

using namespace std;
int a[100];
/*
* �ҳ�����Ȼ��1��2��������m����ȡk������������ϡ�����m=5��k=3
*/
void comb(int m, int k) {
	int i, j;
	for (i = m; i >= k; --i) {
		a[k] = i;
		if (k > 1) comb(i - 1, k - 1);
		else {
			for (j = a[0]; j > 0; --j)
				printf("%d\t", a[j]);
			cout << endl;
		}
	}
}
int main() {
	a[0] = 3;
	comb(5, a[0]);
	return 0;
}