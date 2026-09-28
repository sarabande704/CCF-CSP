#include <bits/stdc++.h>
using namespace std;
int n,d;
long long Q[10005][25],K[10005][25],V[10005][25],res[10005][25];
long long tmp[25][25];
long long W[10005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>d;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=d;++j) {
            cin>>Q[i][j];
        }
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=d;++j) {
            cin>>K[i][j];
        }
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=d;++j) {
            cin>>V[i][j];
        }
    }
    for (int i=1;i<=n;++i) {
        cin>>W[i];
    }
    for (int i=1;i<=d;++i) {
        for (int j=1;j<=d;++j) {
            for (int k=1;k<=n;++k) {
                tmp[i][j]+=K[k][i]*V[k][j];
            }
        }
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=d;++j) {
            for (int k=1;k<=d;++k) {
                res[i][j]+=Q[i][k]*tmp[k][j];
            }
        }
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=d;++j) {
            cout<<res[i][j]*W[i]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}