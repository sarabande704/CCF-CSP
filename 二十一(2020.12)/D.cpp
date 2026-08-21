#include <bits/stdc++.h>
using namespace std;
const int INF=1e9;
int n,m,k,u,v,w,total=0;
vector<vector<int>> need(101,vector<int>(11));
vector<vector<pair<int,int>>> edge(101);
vector<vector<int>> dist(101,vector<int>(11)),len(101,vector<int>(11));

struct Node {
    int d,has,maxl;
};

Node dfs(int root,int fa,int food) {
    Node res={0,0,0};
    if (need[root][food]) {
        res.has=1;
    }
    for (pair<int,int> &child:edge[root]) {
        if (child.first==fa) {
            continue;
        }
        Node tmp=dfs(child.first,root,food);
        if (tmp.has) {
            res.d+=(tmp.d+child.second*2);
            res.maxl=max(res.maxl,tmp.maxl+child.second);
            res.has=1;
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>k;
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=k;++j) {
            cin>>need[i][j];
        }
    }
    for (int i=1;i<n;++i) {
        cin>>u>>v>>w;
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
        total+=w;
    }
    for (int i=1;i<=n;++i) {
        for (int j=1;j<=k;++j) {
            Node p=dfs(i,0,j);
            dist[i][j]=p.d;
            len[i][j]=p.maxl;
        }
    }
    int l=0,r=2*n*total;
    while (l+1<r) {
        int mid=(l+r)>>1;
        vector<int> f(n+1,0);
        for (int i=1;i<=n;++i) {
            for (int j=1;j<=k;++j) {
                if (dist[i][j]-len[i][j]<=mid) {
                    f[i]|=1<<(j-1);
                }
            }
        }
        vector<vector<int>> dp(n+1,vector<int>((1<<k)+1,INF));
        dp[0][0]=0;
        for (int i=0;i<n;++i) {
            for (int j=0;j<=(1<<k)-1;++j) {
                if (dp[i][j]==INF) {
                    continue;
                }
                dp[i+1][j]=min(dp[i+1][j],dp[i][j]);
                dp[i+1][j|f[i+1]]=min(dp[i+1][j|f[i+1]],dp[i][j]+1);
            }
        }
        if (dp[n][(1<<k)-1]<=m) {
            r=mid;
        } else {
            l=mid;
        }
    }
    cout<<r<<'\n';
    return 0;
}