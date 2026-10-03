#include <bits/stdc++.h>
using namespace std;
int n,m,x,y;
vector<pair<int,int>> func;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) {
        pair<int,int> pa;
        cin>>pa.first>>pa.second;
        func.push_back(pa);
    }
    for (int i=1;i<=m;++i) {
        cin>>x>>y;
        for (auto pa:func) {
            x+=pa.first;
            y+=pa.second;
        }
        cout<<x<<" "<<y<<'\n';
    }
    return 0;
}