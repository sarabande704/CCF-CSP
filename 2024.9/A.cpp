#include <bits/stdc++.h>
using namespace std;
int n;
string str;

int main() {
	cin >> n;
	while (n--) {
		cin >> str;
		vector<int> v(300, 0);
		int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 1;
		for (char ch : str) {
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				flag1 = 1;
				if (v[(int)ch] == 2) {
					flag4 = 0;
				}
				++v[(int)ch];
			} else if (ch >= '0' && ch <= '9') {
				flag2 = 1;
				if (v[(int)ch] == 2) {
					flag4 = 0;
				}
				++v[(int)ch];
			} else {
				flag3 = 1;
				if (v[(int)ch] == 2) {
					flag4 = 0;
				}
				++v[(int)ch];
			}
		}
		if (flag1 && flag2 && flag3 && flag4) {
			cout << 2 << endl;
		} else if (flag1 && flag2 && flag3) {
			cout << 1 << endl;
		} else {
			cout << 0 << endl;
		}
	}
	return 0;
}