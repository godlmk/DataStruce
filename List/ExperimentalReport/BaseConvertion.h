#pragma once
#include <iostream>
class Solution {
public:
	Solution(int b) {
		base = b;
		top = 0;
	}
	void print(int n) {
		while (n) {
			stk[top++] = n % base;
			n /= base;
		}

		while (top) {
			std::cout << stk[top - 1];
			--top;
		}
	}

private:
	int base, stk[1000] = { 0 }, top;
};
