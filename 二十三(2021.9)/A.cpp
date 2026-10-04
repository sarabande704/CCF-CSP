#include <bits/stdc++.h>
using namespace std;
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    vector<int> B(n+1,-1);
    int maxs=0,mins=0;
    for (int i=1;i<=n;++i) {
        cin>>B[i];
        maxs+=B[i];
        if (B[i]!=B[i-1]) {
            mins+=B[i];
        }
    }
    cout<<maxs<<'\n'<<mins<<'\n';
    return 0;
}