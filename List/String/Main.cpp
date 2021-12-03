#include <iostream>
#include <string>
#include <vector>
using namespace std;
auto getNext(const vector<char>& t) {
	//��ϣ����ռ��һ������ռ䣬���������� -1��Ϊû��һ��ƥ��ı�־λ
	vector<int> ne(t.size(), -1);
	int i = 0, j = -1;
	while (i < t.size() - 1) {
		if (j == -1 || t[i] == t[j]) {
			//��j == -1������֤����һ���ַ��Ͳ�ƥ�䣬��ʱ��Ҫ��i�����ƶ�һλ����j�ӵ�һλ��ʼ
			++i, ++j;
			ne[i] = j;
		}
		//����ƥ��Ļ�����j��ǰ�ƶ�
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