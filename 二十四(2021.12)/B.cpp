#include <bits/stdc++.h>
using namespace std;
int n,N,g=0,f=0;
vector<int> a(100005,0);
vector<pair<int,int>> vec;
long long res=0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>N;
    for (int i=1;i<=n;++i) {
        cin>>a[i];
        vec.push_back({a[i],1});
    }
    int r=N/(n+1);
    for (int i=r;i<N;i+=r) {
        vec.push_back({i,0});
    }
    vec.push_back({N,1});
    sort(vec.begin(),vec.end());
    int pre=0;
    for (int i=0;i<vec.size();++i) {
        pair<int,int> pa=vec[i];
        res+=(long long)abs(f-g)*(long long)(pa.first-pre);
        if (pa.second) {
            ++f;
        } else {
            ++g;
        }
        pre=pa.first;
    }
    cout<<res<<'\n';
    return 0;
}