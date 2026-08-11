#include <bits/stdc++.h>
using namespace std;
int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> m;
	vector<int> weight = {0};
	vector<int> value = {0};
	vector<vector<int>> dp(n + 5, vector<int>(m + 5, 0));
	int tmp = 0, a;
	for (int i = 1; i <= m; ++i) {
		cin >> a;
		if (a > tmp) {
			weight.push_back(i);
			value.push_back(a);
			tmp = a;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= weight.size() - 1; ++j) {
			if (i < weight[j]) {
				dp[i][j] = dp[i][j - 1];
			} else {
				dp[i][j] = max(dp[i][j - 1], dp[i - weight[j]][j] + value[j]);
			}
		}
	}
	cout << dp[n][weight.size() - 1] << endl;
	return 0;
}
