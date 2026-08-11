#include <bits/stdc++.h>
using namespace std;
long long n, q, p, l, i;
string op;

struct process {
	long long start;
	long long len;
	long long x;  //下一个信息要放置的地方
};
vector<vector<struct process>> v(105);
set<pair<long long, long long>> s;  //存放每一个队列的开始和结尾

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> q;
	while (q--) {
		cin >> op;
		if (op == "new") {
			cin >> p >> l;
			long long empty = -1, w = LLONG_MAX, end = -1;
			for (pair pa : s) {
				if (pa.first - end - 1 >= l && pa.first - end - 1 < w) {
					w = pa.first - end - 1;
					empty = end + 1;
				}
				end = pa.second;
			}
			if (empty == -1) {
				empty = end + 1;
			}
			v[p].push_back({empty, l, empty});
			s.insert({empty, empty + l - 1});
			cout << empty << '\n';
		} else if (op == "send") {
			cin >> p;
			long long res = 0;
			for (struct process &it : v[p]) {
				res += it.x;
				it.x = (it.x + 1 - it.start) % it.len + it.start;
			}
			cout << res << '\n';
		} else {
			cin >> p >> i;
			s.erase({v[p][i - 1].start, v[p][i - 1].start + v[p][i - 1].len - 1});
			v[p].erase(v[p].begin() + i - 1);
		}
	}
	return 0;
}