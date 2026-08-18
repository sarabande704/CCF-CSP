#include <bits/stdc++.h>
using namespace std;
int n,k,x,y,cnt=0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>k>>x>>y;
    queue<pair<int,int>> q,tmp;
    vector<vector<bool>> vis(n+1,vector<bool>(n+1,false));
    q.push({x,y});
    vis[x][y]=true;
    ++cnt;
    while ((!q.empty() || !tmp.empty()) && k) {
        while (!q.empty()) {
            pair<int,int> pa=q.front();
            q.pop();
            x=pa.first;
            y=pa.second;
            if (x>=0 && x<=n-1 && y>=-1 && y<=n-2 && !vis[x+1][y+2]) {
                tmp.push({x+1,y+2});
                vis[x+1][y+2]=1;
                ++cnt;
            }
            if (y>=0 && y<=n-1 && x>=-1 && x<=n-2 && !vis[x+2][y+1]) {
                tmp.push({x+2,y+1});
                vis[x+2][y+1]=1;
                ++cnt;
            }
            if (y>=2 && y<=n+1 && x>=-1 && x<=n-2 && !vis[x+2][y-1]) {
                tmp.push({x+2,y-1});
                vis[x+2][y-1]=1;
                ++cnt;
            }
            if (x>=0 && x<=n-1 && y>=3 && y<=n+2 && !vis[x+1][y-2]) {
                tmp.push({x+1,y-2});
                vis[x+1][y-2]=1;
                ++cnt;
            }
            if (x>=2 && x<=n+1 && y>=3 && y<=n+2 && !vis[x-1][y-2]) {
                tmp.push({x-1,y-2});
                vis[x-1][y-2]=1;
                ++cnt;
            }
            if (y>=2 && y<=n+1 && x>=3 && x<=n+2 && !vis[x-2][y-1]) {
                tmp.push({x-2,y-1});
                vis[x-2][y-1]=1;
                ++cnt;
            }
            if (y>=0 && y<=n-1 && x>=3 && x<=n+2 && !vis[x-2][y+1]) {
                tmp.push({x-2,y+1});
                vis[x-2][y+1]=1;
                ++cnt;
            }
            if (x>=2 && x<=n+1 && y>=-1 && y<=n-2 && !vis[x-1][y+2]) {
                tmp.push({x-1,y+2});
                vis[x-1][y+2]=1;
                ++cnt;
            }
        }
        while (!tmp.empty()) {
            pair<int,int> pa=tmp.front();
            tmp.pop();
            q.push(pa);
        }
        --k;
    }
    cout<<cnt<<'\n';
    return 0;
}