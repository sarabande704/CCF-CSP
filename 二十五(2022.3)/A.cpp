#include <bits/stdc++.h>
using namespace std;
int n,k,x,y,res=0;
vector<bool> vis(100005,false);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k;
    while (k--) {
        cin>>x>>y;
        if (y && !vis[y]) {
            ++res;
        }
        vis[x]=true;
    }
    cout<<res<<'\n';
    return 0;
}