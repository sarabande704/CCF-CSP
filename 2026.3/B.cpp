#include <bits/stdc++.h>
using namespace std;
int n, m, o, t, a, b, k;
double total = 0, maxsub = -1;
vector<pair<double, int>> v1;

vector<pair<int, int>> v2 = {{0, 0}};
vector<vector<int>> dp(1005, vector<int>(210, 0));

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; ++i) {
		cin >> o >> t >> a >> b;
		total += t;
		if (o == 0) {
			v1.push_back({(double)b / a, a});
		} else {
			v2.push_back({a, b});
		}
	}
	sort(v1.begin(), v1.end(), greater<pair<double, int>>());
	sort(v2.begin(), v2.end());
	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j < v2.size(); ++j) {
			if (v2[j].first > i) {
				dp[i][j] = dp[i][j - 1];
			} else {
				dp[i][j] = max(v2[j].second + dp[i - v2[j].first][j - 1], dp[i][j - 1]);
			}
		}
	}
	for (k = 0; k <= m; ++k) {
		int p = k, q = m - k;
		double sub = 0;
		for (int i = 0; i < v1.size() && p > 0; ++i) {
			sub += min(p, v1[i].second) * v1[i].first;
			p -= min(p, v1[i].second);
		}
		sub += dp[q][v2.size() - 1];
		maxsub = max(maxsub, sub);
	}
	cout << fixed << setprecision(6) << total - maxsub << endl;
	return 0;
}
