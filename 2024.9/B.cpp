#include <bits/stdc++.h>
using namespace std;
string s;
int n, m, k;
unordered_map<char, char> f;
unordered_map<char, pair<int, int>> t;
unordered_map<char, vector<char>> res;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	getline(cin, s);
	cin >> n;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string tmp;
	for (int i = 1; i <= n; ++i) {
		getline(cin, tmp);
		f[tmp[1]] = tmp[2];
	}
	for (auto &p : f) {
		if (p.first == p.second) {
			continue;
		}
		char ch1 = p.first, ch2 = p.second;
		vector<bool> vis(130, false);
		vis[(int)ch1] = true;
		vector<int> v(130, 0);
		int cnt = 1;
		res[ch1].push_back(ch1);
		while (1) {
			res[ch1].push_back(ch2);
			if (vis[(int)ch2]) {
				if (ch1 == ch2) {
					t[ch1] = {0, cnt};
				} else {
					t[ch1] = {v[(int)ch2], cnt - v[(int)ch2]};
				}
				break;
			} else {
				vis[(int)ch2] = true;
				v[(int)ch2] = cnt;
				++cnt;
				if (f.find(ch2) != f.end()) {
					ch2 = f[ch2];
				}
			}
		}
	}
	cin >> m;
	while (m--) {
		cin >> k;
		string str = s;
		for (char &ch : str) {
			if (res.find(ch) != res.end()) {
				if (k <= t[ch].first) {
					ch = res[ch][k];
				} else {
					ch = res[ch][(k - t[ch].first) % (t[ch].second) + t[ch].first];
				}
			}
		}
		cout << str << '\n';
	}
	return 0;
}
