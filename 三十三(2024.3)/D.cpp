#include <bits/stdc++.h>
using namespace std;
int c,m,n,x,w,p,cnt=0;
vector<int> pre(3e5+5,0),nxt(3e5+5,0),water(3e5+5,0),np(3e5+5,0);
unordered_map<int,int> pn,tmp;

void dfs(int id) {
    if (water[id]<5) {
        return;
    }
    water[id]=0;
    --cnt;
    int l=pre[id],r=nxt[id];
    if (l>0 && l<=m) {
        ++water[l];
        nxt[l]=r;
    }
    if (r>0 && r<=m) {
        ++water[r];
        pre[r]=l;
    }
    if (l>0 && l<=m && water[l]>=5) {
        dfs(l);
    }
    if (r>0 && r<=m && water[r]>=5) {
        dfs(r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>c>>m>>n;
    for (int i=1;i<=m;++i) {
        cin>>x>>w;
        tmp[x]=w;
        np[i]=x;
        ++cnt;
    }
    sort(np.begin()+1,np.begin()+m+1);
    for (int i=1;i<=m;++i) {
        pn[np[i]]=i;
        pre[i]=i-1;
        nxt[i]=i+1;
        water[i]=tmp[np[i]];
    }
    while (n--) {
        cin>>p;
        int id=pn[p];
        ++water[id];
        dfs(id);
        cout<<cnt<<'\n';
    }
    return 0;
}