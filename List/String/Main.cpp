#include <iostream>
#include <string>
#include <vector>
using namespace std;
auto getNext(const vector<char>& t) {
	//不希望多占用一个数组空间，所以我们让 -1成为没有一个匹配的标志位
	vector<int> ne(t.size(), -1);
	int i = 0, j = -1;
	while (i < t.size() - 1) {
		if (j == -1 || t[i] == t[j]) {
			//若j == -1，则则证明第一个字符就不匹配，这时需要把i往后移动一位，而j从第一位开始
			++i, ++j;
			ne[i] = j;
		}
		//若不匹配的话，则j往前移动
		else j = ne[j];
	}
	return ne;
}
int Find(const vector<char>& s, const vector<char>& t) {
	auto ne = getNext(t);
	int len1 = s.size(), len2 = t.size();
	int i = 0, j = -1;
	while (i < len1 && j < len2)
	{
		if (j == -1 || s[i] == t[j])
			++i, ++j;
		else j = ne[j];
	}
	if (j == (int)t.size()) return i - len2;
	else return -1;
}
int main()
{
	vector t{ 'a','b','a','a','b','c','a','c' };
	vector s{ 'z','b','i','a','b','a','a','b','c','a','c' };
	cout << Find(s, t);
	return 0;
}