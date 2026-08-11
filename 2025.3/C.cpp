#include <bits/stdc++.h>
using namespace std;
int m = 1000000007;
int n, op;
string var, line, item;
unordered_map<string, long long> mp1;
unordered_map<string, vector<string>> mp2;
int timer = 0;
unordered_map<string, int> cachetime, cachelen;

int mylen(string s) {
	if (mp2.count(s)) {
		if (cachetime[s] == timer) {
			return cachelen[s];
		}
		long long len = 0;
		for (string it : mp2[s]) {
			if (it[0] != '$') {
				len = (len + it.length()) % m;
			} else {
				len = (len + mylen(it.substr(1))) % m;
			}
		}
		cachetime[s] = timer;
		cachelen[s] = len;
		return len;
	}
	if (mp1.count(s)) {
		return mp1[s] % m;
	}
	return 0;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n;
	while (n--) {
		cin >> op >> var;
		if (op == 1) {
			getline(cin, line);
			stringstream ss(line);
			long long len = 0;
			while (ss >> item) {
				if (item[0] != '$') {
					len = (len + item.length()) % m;
				} else {
					len = (len + mylen(item.substr(1))) % m;
				}
			}
			mp2.erase(var);
			mp1[var] = len;
			++timer;
		} else if (op == 2) {
			mp1.erase(var);
			mp2[var].clear();
			getline(cin, line);
			stringstream ss(line);
			while (ss >> item) {
				mp2[var].push_back(item);
			}
			++timer;
		} else {
			cout << mylen(var) << '\n';
		}
	}
	return 0;
}
