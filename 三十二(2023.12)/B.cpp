#include <bits/stdc++.h>
using namespace std;
int q,k;
long long n;

void solve() {
    unordered_map<long long,int> mp; //存储质因子及其幂次
    long long d=2;
    while (d*d<=n) {
        while (n%d==0) {
            ++mp[d];
            n/=d;
        }
        if (d!=2) {
            d+=2;
        } else {
            d+=1;
        }
    }
    if (n>1) {
        ++mp[n];
    }
    long long res=1;
    for (auto it:mp) {
        long long a=it.first,b=it.second;
        if (b>=k) {
            res=res*(long long)pow(a,b);
        }
    }
    cout<<res<<'\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>q;
    while (q--) {
        cin>>n>>k;
        solve();
    }
    return 0;
}