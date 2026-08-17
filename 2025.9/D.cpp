#include <bits/stdc++.h>
using namespace std;
const int MAXN=2e5+5;
int n,m;
vector<int> val(MAXN);
vector<vector<int>> edge(MAXN);
vector<int> dep(MAXN);  //深度
vector<int> s(MAXN,MAXN);  //存储某节点子树中，除了这个节点外的最小权值
vector<int> ss(MAXN,MAXN+1);  //同上，存次小值
vector<int> sss(MAXN,MAXN+2);  //同上，存次次小值
vector<int> h(MAXN,MAXN);  //存储整棵树去掉以当前节点为根的子树后，最小权值
vector<vector<int>> f(18,vector<int>(MAXN));  //祖先
vector<vector<int>> g(18,vector<int>(MAXN,MAXN));  //g[i][j]为f[i][j]的子树除去以j为根的子树和从j到f[i][j]上的点后的最小权值

int dfs1(int root,int fa) {
    dep[root]=dep[fa]+1;
    f[0][root]=fa;
    int res=val[root];
    for (int child:edge[root]) {
        if (child==fa) {
            continue;
        }
        int tmp=dfs1(child,root);
        res=min(res,tmp);
        if (tmp<s[root]) {
            ss[root]=s[root];
            s[root]=tmp;
        } else if (tmp<ss[root]) {
            sss[root]=ss[root];
            ss[root]=tmp;
        } else if (tmp<sss[root]) {
            sss[root]=tmp;
        }
    }
    return res;
}

void dfs2(int root,int fa) {
    for (int child:edge[root]) {
        if (child==fa) {
            continue;
        }
        h[child]=min(h[root],val[root]);
        if (s[root]==min(val[child],s[child])) {
            h[child]=min(h[child],ss[root]);
        } else {
            h[child]=min(h[child],s[root]);
        }
        dfs2(child,root);
    }
}

void pre() {
    for (int j=1;j<=n;++j) {
        int fa=f[0][j];
        if (s[fa]==min(val[j],s[j])) {
            g[0][j]=ss[fa];
        } else {
            g[0][j]=s[fa];
        }
    }
    for (int i=1;i<=17;++i) {
        for (int j=1;j<=n;++j) {
            f[i][j]=f[i-1][f[i-1][j]];
            g[i][j]=min(g[i-1][j],g[i-1][f[i-1][j]]);
        }
    }
}

pair<int,int> lca(int u,int v) {
    int res=MAXN;
    for (int i=17;i>=0;--i) {
        if (dep[f[i][u]]>=dep[v]) {
            res=min(res,g[i][u]);
            u=f[i][u];
        }
    }
    if (u==v) {
        return {v,res};
    }
    for (int i=17;i>=0;--i) {
        if (f[i][u]!=f[i][v]) {
            res=min(res,min(g[i][u],g[i][v]));
            u=f[i][u];
            v=f[i][v];
        }
    }
    int l=f[0][v];  //要求的最近公共祖先
    int tu=min(val[u],s[u]),tv=min(val[v],s[v]);  //u,v所在子树的最小权值
    if (s[l]!=tu && s[l]!=tv) {
        res=min(res,s[l]);
    } else if (ss[l]!=tu && ss[l]!=tv) {
        res=min(res,ss[l]);
    } else {
        res=min(res,sss[l]);
    }
    return {l,res};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) { 
        cin>>val[i];
    }
    int x,y;
    for (int i=1;i<n;++i) {
        cin>>x>>y;
        edge[x].push_back(y);
        edge[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0);
    pre();
    while (m--) {
        cin>>x>>y;
        if (dep[x]<dep[y]) {
            swap(x,y);
        }
        pair<int,int> w=lca(x,y);
        if (w.first==y) {
            int res=min(min(s[x],h[y]),w.second);
            if (res>=n) {
                cout<<n<<'\n';
            } else {
                cout<<res<<'\n';
            }
        } else {
            int res=min(min(s[x],s[y]),min(h[w.first],w.second));
            if (res>=n) {
                cout<<n<<'\n';
            } else {
                cout<<res<<'\n';
            }
        }
    }
    return 0;
}