#include <bits/stdc++.h>
using namespace std;
int n,x,total=0;
vector<int> a(35);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>x;
    for (int i=1;i<=n;++i) {
        cin>>a[i];
        total+=a[i];
    }
    vector<vector<int>> dp(total-x+1,vector<int>(n+1,0));
    for (int i=1;i<=total-x;++i) {
        for (int j=1;j<=n;++j) {
            dp[i][j]=dp[i][j-1];
            if (i>=a[j]) {
                dp[i][j]=max(dp[i][j],dp[i-a[j]][j-1]+a[j]);
            }
        }
    }
    cout<<total-dp[total-x][n]<<'\n';
    return 0;
}