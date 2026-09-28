#include <bits/stdc++.h>
using namespace std;
int n,m,k,u,v,w;
long long res=0;
vector<vector<long long>> cost(10005,vector<long long>(12,0)); //变电站造价
vector<unordered_set<int>> edge(10005); //存储到达的点
map<pair<int,int>,vector<vector<long long>>> d; //电线造价
vector<int> in(10005,0); //每个点的度
unordered_set<int> s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>k;
    for (int i=0;i<n;++i) {
        for (int j=0;j<k;++j) {
            cin>>cost[i][j];
        }
    }
    vector<vector<long long>> vec1(k,vector<long long>(k)),vec2(k,vector<long long>(k));
    for (int i=0;i<m;++i) {
        cin>>u>>v;
        edge[u].insert(v);
        edge[v].insert(u);
        ++in[u];
        ++in[v];
        for (int j=0;j<k;++j) {
            for (int t=0;t<k;++t) {
                cin>>vec1[j][t];
                vec2[t][j]=vec1[j][t];
            }
        }
        d[{u,v}]=vec1;
        d[{v,u}]=vec2;
    }
    for (int i=0;i<n;++i) {
        if (in[i]>2) {
            continue;
        }
        s.insert(i);
    }
    while (!s.empty()) {
        v=*(s.begin());
        s.erase(v);
        if (in[v]==0) {
            long long ans=LLONG_MAX;
            for (int i=0;i<k;++i) {
                ans=min(ans,cost[v][i]);
            }
            res+=ans;
        } else if (in[v]==1) {
            u=*(edge[v].begin());
            for (int i=0;i<k;++i) {
                long long mini=LLONG_MAX;
                for (int j=0;j<k;++j) {
                    mini=min(mini,cost[v][j]+d[{v,u}][j][i]);
                }
                cost[u][i]+=mini;
            }
            edge[v].erase(u);
            edge[u].erase(v);
            --in[u];
            if (in[u]>2) {
                continue;
            }
            if (s.find(u)!=s.end()) {
                s.erase(u);
            }
            s.insert(u);
        } else if (in[v]==2) {
            u=*(edge[v].begin());
            edge[u].erase(v);
            edge[v].erase(u);
            w=*(edge[v].begin());
            edge[w].erase(v);
            edge[v].erase(w);
            if (d.find({u,w})==d.end()) {
                d[{u,w}]=d[{w,u}]=vector<vector<long long>>(k,vector<long long>(k,0));
                edge[u].insert(w);
                edge[w].insert(u);
            } else {
                if (--in[u]<=2) {
                    if (s.find(u)!=s.end()) {
                        s.erase(u);
                    }
                    s.insert(u);
                }
                if (--in[w]<=2) {
                    if (s.find(w)!=s.end()) {
                        s.erase(w);
                    }
                    s.insert(w);
                }
            }
            for (int j=0;j<k;++j) {
                for (int t=0;t<k;++t) {
                    long long mini=LLONG_MAX;
                    for (int i=0;i<k;++i) {
                        mini=min(mini,cost[v][i]+d[{v,u}][i][j]+d[{v,w}][i][t]);
                    }
                    d[{u,w}][j][t]+=mini;
                    d[{w,u}][t][j]+=mini;
                }
            }
        }
    }
    int cnt=0; //剩余的节点数
    vector<int> id(6); //存储新编号对应的节点
    unordered_map<int,int> mp; //存储老编号对应的新编号
    vector<int> state(6);
    for (int i=0;i<n;++i) {
        if (in[i]>2) {
            id[cnt]=i;
            mp[i]=cnt;
            ++cnt;
        }
    }
    long long ans=LLONG_MAX;
    for (int i=0;i<(pow)(10,cnt);++i) {
        int tmp=i,div=10,j;
        for (j=0;j<cnt;++j) {
            state[j]=tmp%div;
            if (state[j]>=k) {
                break;
            }
            tmp/=div;
        }
        if (j!=cnt) {
            continue;
        }
        long long total=0;
        for (j=0;j<cnt;++j) {
            int pos=id[j];
            u=state[j];
            for (int child:edge[pos]) {
                w=state[mp[child]];
                total+=d[{pos,child}][u][w];
            }
        }
        total>>=1;
        for (j=0;j<cnt;++j) {
            total+=cost[id[j]][state[j]];
        }
        ans=min(ans,total);
    }
    cout<<res+ans<<'\n';
    return 0;
}