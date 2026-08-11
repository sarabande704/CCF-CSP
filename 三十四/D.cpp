#include <bits/stdc++.h>
using namespace std;
int n,m,v;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>v;
    int total_cost=0;  //最大花费
    vector<vector<pair<int,int>>> repo_goods(n);  //记录每个仓库都有哪些货物及其价值（价值在前）
    vector<int> repo_base(n);  //记录每个仓库的起价
    vector<int> repo_cost(n);  //记录仓库运输货物的单价
    for (int i=0;i<n;++i) {
        cin>>repo_base[i]>>repo_cost[i];
        total_cost+=repo_base[i];
    }
    for (int i=0;i<m;++i) {
        int price,id;
        cin>>price>>id;
        repo_goods[id].push_back({price,i});
    }
    for (int i=0;i<n;++i) {
        total_cost+=(repo_goods[i].size()*repo_cost[i]);
    }
    vector<vector<pair<int,int>>> repo(n);  //存放每个仓库的不同方案下的花费（还要算上基本价）和利润
    //从一个仓库中取货物，虽然方案很多，但是运输单价一样，所以按价值排序
    for (int i=0;i<n;++i) {
        sort(repo_goods[i].begin(),repo_goods[i].end(),greater<pair<int,int>>());
    }
    for (int i=0;i<n;++i) {
        int pre_price=0,pre_cost=repo_base[i];
        for (int j=0;j<repo_goods[i].size();++j) {
            pre_price+=repo_goods[i][j].first;
            pre_cost+=repo_cost[i];
            repo[i].push_back({pre_cost,pre_price-pre_cost});
        }
    }
    vector<vector<int>> dp(total_cost+5,vector<int>(n+1,0));
    for (int i=1;i<=total_cost;++i) {
        for (int j=1;j<=n;++j) {
            dp[i][j]=dp[i][j-1];
            for (int k=0;k<repo[j-1].size();++k) {
                if (repo[j-1][k].first<=i) {
                    dp[i][j]=max(dp[i][j],dp[i-repo[j-1][k].first][j-1]+repo[j-1][k].second);
                    if (dp[i][j]>=v) {
                        cout<<i<<endl;
                        exit(0);
                    }
                }
            }
        }
    }
    return 0;
}