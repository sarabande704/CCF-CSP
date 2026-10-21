#include <bits/stdc++.h>
using namespace std;
int n,m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    vector<vector<int>> repo(n+1,vector<int>(m+1,0));
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=m;++j) {
            cin>>repo[i][j];
        }
    }
    for (int i=1;i<=n;++i) {
        int pa=0;
        for (int j=1;j<=n;++j) {
            if (j!=i) {
                int k;
                for (k=1;k<=m;++k) {
                    if (repo[j][k]<=repo[i][k]) {
                        break;
                    }
                }
                if (k>m) {
                    pa=j;
                    break;
                }
            }
        }
        cout<<pa<<'\n';
    }
    return 0;
}