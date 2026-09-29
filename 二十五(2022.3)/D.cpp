#include <bits/stdc++.h>
using namespace std;
int n,m,pa=0,island,k,l;
vector<set<pair<long long,int>>> edge(100005); //存储所有通信对象
vector<int> to(100005); //存储通信主要对象
map<pair<int,int>,long long> mp; //存储每对通信对象之间的额度

struct task {
    int u,v,y;
    long long x;
};
vector<vector<task>> event(100005);

struct query {
    vector<int> vec;
    int p,q;
};
vector<query> ask(100005);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    island=n;
    for (int i=1;i<=m;++i) {
        cin>>k;
        while (k--) {
            task t;
            cin>>t.u>>t.v>>t.x>>t.y;
            event[i].push_back(t);
            if (i+t.y<=m) {
                t.x*=(-1);
                event[i+t.y].push_back(t);
            }
        }
        cin>>l;
        int id;
        query que;
        while (l--) {
            cin>>id;
            que.vec.push_back(id);
        }
        cin>>que.p>>que.q;
        ask[i]=que;
    }
    for (int i=1;i<=m;++i) {
        //更新
        for (auto it:event[i]) {
            int u=min(it.u,it.v),v=max(it.u,it.v);
            int oldu=to[u],oldv=to[v];
            int newu=0,newv=0;
            if (it.x>0) {
                if (!to[u]) {
                    --island;
                }
                if (!to[v]) {
                    --island;
                }
                if (edge[u].find({mp[{u,v}]*(-1),v})!=edge[u].end()) {
                    pair<long long,int> p1=*(edge[u].find({mp[{u,v}]*(-1),v}));
                    pair<long long,int> p2=*(edge[v].find({mp[{u,v}]*(-1),u}));
                    edge[u].erase(p1);
                    edge[v].erase(p2);
                    p1.first-=it.x;
                    p2.first-=it.x;
                    edge[u].insert(p1);
                    edge[v].insert(p2);
                } else {
                    edge[u].insert({it.x*(-1),v});
                    edge[v].insert({it.x*(-1),u});
                }
                newu=edge[u].begin()->second;
                newv=edge[v].begin()->second;
            } else {
                pair<long long,int> p1=*(edge[u].find({mp[{u,v}]*(-1),v}));
                pair<long long,int> p2=*(edge[v].find({mp[{u,v}]*(-1),u}));
                edge[u].erase(p1);
                edge[v].erase(p2);
                p1.first-=it.x;
                p2.first-=it.x;
                if (p1.first) {
                    edge[u].insert(p1);
                }
                if (p2.first) {
                    edge[v].insert(p2);
                }
                if (!edge[u].empty()) {
                    newu=edge[u].begin()->second;
                }
                if (!edge[v].empty()) {
                    newv=edge[v].begin()->second;
                }
                if (oldu && !newu) {
                    ++island;
                }
                if (oldv && !newv) {
                    ++island;
                }
            }
            if (oldu!=newu) {
                if (oldu && to[oldu]==u) {
                    --pa;
                }
                to[u]=newu;
                if (newu && to[newu]==u) {
                    ++pa;
                }
            }
            if (oldv!=newv) {
                if (oldv && to[oldv]==v) {
                    --pa;
                }
                to[v]=newv;
                if (newv && to[newv]==v) {
                    ++pa;
                }
            }
            mp[{u,v}]+=it.x;
        }
        //查找
        auto it=ask[i];
        for (auto tmp:it.vec) {
            cout<<to[tmp]<<'\n';
        }
        if (it.p) {
            cout<<island<<'\n';
        }
        if (it.q) {
            cout<<pa<<'\n';
        }
    }
    return 0;
}