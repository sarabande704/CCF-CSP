#include <bits/stdc++.h>
using namespace std;
int n,m,k,t,c,q;
vector<int> suf(200005,0); //差分数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>k;
    for (int i=1;i<=n;++i) {
        cin>>t>>c;
        if (t-k>0) {
            ++suf[max(t-k-c+1,1)];
            --suf[t-k+1];
        }
    }
    for (int i=1;i<=200000;++i) {
        suf[i]+=suf[i-1];
    }
    while (m--) {
        cin>>q;
        cout<<suf[q]<<'\n';
    }
    return 0;
}