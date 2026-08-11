#include <bits/stdc++.h>
using namespace std;
int n,m,l,w;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    vector<unordered_set<int>> p(m+1);
    unordered_map<int,int> total;
    for (int i=1;i<=n;++i) {
        cin>>l;
        while (l--) {
            cin>>w;
            p[w].insert(i);
            ++total[w];
        }
    }
    for (int i=1;i<=m;++i) {
        cout<<p[i].size()<<" "<<total[i]<<endl;
    }
    return 0;
}