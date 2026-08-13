#include <bits/stdc++.h>
using namespace std;
int n,t,k,res=0;
long long c,m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>k;
    set<int,greater<int>> field;
    unordered_map<int,long long> cost;
    while (n--) {
        cin>>t>>c;
        res=max(res,t);
        if (field.find(t)==field.end()) {
            field.insert(t);
        }
        cost[t]+=c;
    }
    while (1) {
        int tmp=*(field.begin());
        if (tmp==k || cost[tmp]>m) {
            break;
        }
        field.erase(field.begin());
        m-=cost[tmp];
        cost[tmp-1]+=cost[tmp];
        if (field.find(tmp-1)==field.end()) {
            field.insert(tmp-1);
        }
        res=tmp-1;
    }
    cout<<res<<endl;
    return 0;
}