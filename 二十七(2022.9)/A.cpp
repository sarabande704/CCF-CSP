#include <bits/stdc++.h>
using namespace std;
int n,m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    vector<int> a(n+1),c(n+1,1);
    for (int i=1;i<=n;++i) {
        cin>>a[i];
        c[i]=a[i]*c[i-1];
    }
    vector<int> b(n+1);
    int pre=0;
    for (int i=1;i<=n;++i) {
        int tmpm=m%c[i];
        tmpm-=pre;
        b[i]=tmpm/c[i-1];
        pre+=c[i-1]*b[i];
    }
    for (int i=1;i<=n;++i) {
        cout<<b[i]<<" ";
    }
    return 0;
}