#include <bits/stdc++.h>
using namespace std;
int n,m;
const int INF=2000000000;

struct Node {
    int id;
    int l;
    bool operator<(const Node &o) const {
        return l>o.l;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    vector<pair<int,int>> v={{0,0}};  //节点坐标
    vector<vector<pair<int,int>>> edge(n+m+1);  //图，用虚拟节点，把基站也算作一个节点
    for (int i=1;i<=n;++i) {
        int x,y;
        cin>>x>>y;
        v.push_back({x,y});
    }
    for (int i=1;i<=m;++i) {
        int x,y,r,t;
        cin>>x>>y>>r>>t;
        for (int j=1;j<=n;++j) {
            int p=v[j].first,q=v[j].second;
            if (p<=x+r && p>=x-r && q<=y+r && q>=y-r) {
                edge[j].push_back({n+i,t});
                edge[n+i].push_back({j,0});
            }
        }
    }
    vector<int> dist(n+m+1,INF);
    dist[1]=0;
    vector<bool> vis(n+m+1,false);
    priority_queue<Node> pq;
    pq.push({1,0});
    while (!pq.empty()) {
        Node p=pq.top();
        pq.pop();
        if (vis[p.id]) {
            continue;
        }
        vis[p.id]=true;
        for (auto it:edge[p.id]) {
            if (dist[it.first]>it.second+dist[p.id]) {
                dist[it.first]=it.second+dist[p.id];
                pq.push({it.first,dist[it.first]});
            }
        }
    }
    if (dist[n]==INF) {
        cout<<"Nan"<<endl;
    } else {
        cout<<dist[n]<<endl;
    }
    return 0;
}