#include <bits/stdc++.h>
using namespace std;
int n,om;
double oq;
vector<int> value(105);
vector<double> vec(105);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>om>>oq;
	unsigned long long q=(unsigned long long)(1000*oq)*(unsigned long long)(1000*oq);
	unsigned long long m=(unsigned long long)100000000*om*om;
	unsigned long long tmp=m/q;
	for (int i=1;i<=n;++i) {
		cin>>value[i];
	}
	for (int i=1;i<=n;++i) {
		cin>>vec[i];
	}
	vector<vector<int>> dp(105,vector<int>(tmp+5,0));
	for (int i=1;i<=n;++i) {
		for (unsigned long long j=1;j<=tmp;++j) {
			dp[i][j]=dp[i-1][j];
			unsigned long long t=(unsigned long long)(vec[i]*10)*(unsigned long long)(vec[i]*10);
			if (j>=t) {
				dp[i][j]=max(dp[i][j],dp[i-1][j-t]+value[i]);
			}
		}
	}
	cout<<dp[n][tmp]<<'\n';
    return 0;
}