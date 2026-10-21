#include <bits/stdc++.h>
using namespace std;
int n,m,cnt=0;
vector<long long> val(2005);
vector<vector<int>> edge(2005);
vector<int> fa(2005);
vector<int> dfn(2005);
vector<long long> weight(2005);
vector<int> sz(2005);

int dfs(int x) {
    dfn[x]=++cnt;
    weight[x]+=val[x];
    sz[x]=1;
    for (int child:edge[x]) {
        sz[x]+=dfs(child);
        weight[x]+=weight[child];
    }
    return sz[x];
}

//检查u是否为v的祖先
bool check(int u,int v) {
    return dfn[v]>=dfn[u] && dfn[v]<=dfn[u]+sz[u]-1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) {
        cin>>val[i];
    }
    for (int i=2;i<=n;++i) {
        cin>>fa[i];
        edge[fa[i]].push_back(i);
    }
    dfs(1);
    long long total; //总权值
    int cnt1; //剩余的待检查节点数
    vector<bool> alive(2005); //检验该节点是否被淘汰
    vector<long long> tmp(2005); //存储子树的总权值
    while (m--) {
        int t;
        cin>>t;
        total=weight[1];
        cnt1=n;
        for (int i=1;i<=n;++i) {
            alive[i]=1;
            tmp[i]=weight[i];
        }
        while (cnt1>1) {
            int id=2005;
            long long cmp=20000000005;
            for (int i=1;i<=n;++i) {
                if (alive[i]) {
                    if (abs(2*tmp[i]-total)<cmp || (abs(2*tmp[i]-total)==cmp && i<id)) {
                        id=i;
                        cmp=abs(2*tmp[i]-total);
                    }
                }
            }
            cout<<id<<" ";
            cnt=0;
            if (check(id,t)) {
                for (int i=1;i<=n;++i) {
                    if (!alive[i]) {
                        continue;
                    }
                    if (!check(id,i)) {
                        alive[i]=0;
                    } else {
                        ++cnt;
                    }
                }
                cnt1=cnt;
                total=tmp[id];
            } else {
                for (int i=1;i<=n;++i) {
                    if (!alive[i]) {
                        continue;
                    }
                    if (check(id,i)) {
                        alive[i]=0;
                    } else {
                        ++cnt;
                        if (check(i,id)) {
                            tmp[i]-=tmp[id];
                        }
                    }
                }
                cnt1=cnt;
                total-=tmp[id];
            }
        }
        cout<<'\n';
    }
    return 0;
}