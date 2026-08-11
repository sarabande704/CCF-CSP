#include <bits/stdc++.h>
using namespace std;
int n, a, b;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> a;
	vector<int> pre_sum(n + 1), pre_max(n + 1), suf_max(n + 1), va(n + 1), vb(n + 1);
	for (int i = 1; i <= n; ++i) {
		cin >> va[i];
	}
	for (int i = 1; i <= n; ++i) {
		cin >> vb[i];
		pre_sum[i] = pre_sum[i - 1] + va[i] - vb[i];
	}
	int tmp = -1000000000;
	for (int i = 1; i <= n; ++i) {
		tmp = max(tmp, pre_sum[i]);
		pre_max[i] = tmp;
	}
	tmp = -1000000000;
	for (int i = n; i >= 1; --i) {
		tmp = max(tmp, pre_sum[i]);
		suf_max[i] = tmp;
	}
	for (int i = 1; i <= n; ++i) {
		int res = max(pre_max[i - 1], suf_max[i] + vb[i]);
		res = max(res, 0) + a;
		cout << res << ' ';
	}
	return 0;
}