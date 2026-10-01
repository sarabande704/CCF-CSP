#include <bits/stdc++.h>
using namespace std;
int n,N,res=0;
vector<int> a(205,0);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>N;
    for (int i=1;i<=n;++i) {
        cin>>a[i];
    }
    for (int i=0;i<=n;++i) {
        if (i!=n) {
            res+=i*(a[i+1]-a[i]);
        } else {
            res+=i*(N-a[i]);
        }
    }
    cout<<res<<'\n';
    return 0;
}