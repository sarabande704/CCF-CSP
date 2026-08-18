#include <bits/stdc++.h>
using namespace std;
const int MAXN=1e5+5;
int n,a[MAXN],k[MAXN],fa[MAXN];

int find(int x) {
    return x==fa[x] ? x : fa[x]=find(fa[x]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    if (n==1) {
        cout<<0<<'\n';
        exit(0);
    }
    for (int i=1;i<=n;++i) {
        cin>>a[i];
    } 
    for (int i=1;i<=n;++i) {
        cin>>k[i];
    }
    for (int i=1;i<=n+1;++i) {
        fa[i]=i;
    }
    vector<int> dist(n+1,-1);
    dist[1]=0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int p=q.front();
        q.pop();
        int l=p+1,r=min(p+k[p],n);
        int cur=find(l);
        while (cur<=r) {
            int to=cur-a[cur];
            int nxt=find(cur+1);
            if (dist[to]==-1) {
                dist[to]=dist[p]+1;
                if (to==n) {
                    cout<<dist[to]<<'\n';
                    exit(0);
                }
                q.push(to);
            }
            fa[cur]=nxt;
            cur=nxt;
        }
    }
    cout<<-1<<'\n';
    return 0;
}