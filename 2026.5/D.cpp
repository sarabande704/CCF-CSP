#include <bits/stdc++.h>
using namespace std;
int n,q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>q;
    vector<int> stones(n+1,0),pre_odd(n,0),pre_even(n,0);
    for (int i=1;i<=n;++i) {
        cin>>stones[i];
        int id;
        if (i%2) {
            id=(i+1)/2;
            pre_odd[id]=pre_odd[id-1]^stones[i];
        } else {
            id=i/2;
            pre_even[id]=pre_even[id-1]^stones[i];
        }
    } 
    unordered_map<int,int> mp_odd,mp_even;  //记录<异或值，原数组位置>
    vector<int> dis(n+1,INT_MAX);  //记录每个起点的最近的终点
    vector<int> suf(n+2,INT_MAX);  //记录>=i的所有起点中，最靠左边的终点
    vector<int> f(n+1,INT_MAX);  //记录从每个点出并跳到最近的符合要求的点后，下一个起点是什么
    for (int i=n;i>=1;--i) {
        int id;
        if (i%2) {
            id=(i+1)/2;
            mp_odd[pre_odd[id]]=i;
            if (mp_odd[pre_odd[id-1]]) {
                dis[i]=mp_odd[pre_odd[id-1]];
            }
        } else {
            id=i/2;
            mp_even[pre_even[id]]=i;
            if (mp_even[pre_even[id-1]]) {
                dis[i]=mp_even[pre_even[id-1]];
            }
        }
        suf[i]=min(suf[i+1],dis[i]);
        if (suf[i]!=INT_MAX) {
            f[i]=suf[i]+1;
        }
    }
    vector<vector<int>> up(20,vector<int>(n+2,INT_MAX));  //up[i][j]=从j号点出发，跳2^i次后，到达的新的起点
    for (int i=1;i<=n;++i) {
        up[0][i]=f[i];
    }
    for (int i=1;i<=19;++i) {
        for (int j=1;j<=n;++j) {
            if (up[i-1][j]!=INT_MAX) {
                up[i][j]=up[i-1][up[i-1][j]];
            }
        }
    }
    int l,r;
    while (q--) {
        cin>>l>>r;
        int res=0;
        for (int i=19;i>=0;--i) {
            if (l>r) {
                break;
            }
            if (up[i][l]<=r+1) {
                l=up[i][l];
                res+=(int)pow(2,i);
            }
        }
        cout<<res<<'\n';
    }
    return 0;
}