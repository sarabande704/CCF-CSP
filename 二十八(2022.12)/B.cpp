#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<int> fa(105),root,day(105),start(105),last(105),total(105);
vector<vector<int>> child(105);

int dfs(int r) {
    if (child[r].size()==0) {
        total[r]=day[r];
        return total[r];
    }
    int t=0;
    for (int ch:child[r]) {
        t=max(t,dfs(ch));
    }
    t+=day[r];
    total[r]=t;
    return total[r];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=m;++i) {
        cin>>fa[i];
        if (fa[i]) {
            child[fa[i]].push_back(i);
        } else {
            root.push_back(i);
        }
    }
    for (int i=1;i<=m;++i) {
        cin>>day[i];
    }
    for (int i=1;i<=m;++i) {
        if (!fa[i]) {
            start[i]=1;
        } else {
            int pre=fa[i];
            while (pre) {
                start[i]+=day[pre];
                pre=fa[pre];
            }
            start[i]+=1;
        }
    }
    int flag=1;
    for (int r:root) {
        dfs(r);
    }
    for (int i=1;i<=m;++i) {
        last[i]=n-total[i]+1;
        if (last[i]<start[i]) {
            flag=0;
            break;
        }
    }
    for (int i=1;i<=m;++i) {
        cout<<start[i]<<" ";
    }
    cout<<'\n';
    if (flag) {
        for (int i=1;i<=m;++i) {
            cout<<last[i]<<" ";
        }
    }
    return 0;
}