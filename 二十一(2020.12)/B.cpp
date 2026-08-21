#include <bits/stdc++.h>
using namespace std;
int m;
vector<pair<int,int>> vec(2e5+5); 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>m;
    unordered_set<int> s;
    for (int i=1;i<=m;++i) {
        cin>>vec[i].first>>vec[i].second;
    }
    sort(vec.begin()+1,vec.begin()+m+1);
    vector<int> pre(m+1,0);
    for (int i=1;i<=m;++i) {
        pre[i]=pre[i-1]+vec[i].second;
    }
    int res=-1,pass=-1;
    for (int i=1;i<=m;++i) {
        auto it=lower_bound(vec.begin()+1,vec.begin()+m+1,(pair<int,int>){vec[i].first,0});
        int j=it-vec.begin();
        int tmp=(j-1-pre[j-1])+(pre[m]-pre[j-1]);
        if (tmp>=pass) {
            res=vec[i].first;
            pass=tmp;
        }
    }
    cout<<res<<'\n';
    return 0;
}