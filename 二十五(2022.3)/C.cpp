#include <bits/stdc++.h>
using namespace std;
int n,m,l,g,f,a,na,pa,paa,paar;
vector<int> fa(1005); //每个节点属于的区域
vector<int> cnt(1005); //每个节点运行的任务数
vector<bitset<1001>> block(1005); //每个区块包含哪些节点
unordered_map<int,unordered_set<int>> mp; //应用在哪些区域运行
unordered_map<int,bitset<1001>> task; //应用在哪些节点运行

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) {
        cin>>l;
        fa[i]=l;
        block[l].set(i);
    }
    cin>>g;
    while (g--) {
        cin>>f>>a>>na>>pa>>paa>>paar;
        while (f--) {
            bitset<1001> bs;
            bs.set();
            bs.reset(0);
            //需求一
            if (na) {
                bs&=block[na];
            }
            //需求二
            bitset<1001> tmp;
            if (pa) {
                for (int it:mp[pa]) {
                    tmp|=block[it];
                }
                bs&=tmp;
            }
            if (bs.none()) {
                cout<<0<<" ";
                continue;
            }
            //需求三
            bitset<1001> bs1(bs);
            if (paa) {
                bs&=(~task[paa]);
            }
            if (bs.none()) {
                if (paar) {
                    cout<<0<<" ";
                    continue;
                } else {
                    bs=bs1;
                }
            }
            //分配节点
            vector<pair<int,int>> vec;
            for (int i=1;i<=n;++i) {
                if (bs.test(i)) {
                    vec.push_back({cnt[i],i});
                }
            }
            sort(vec.begin(),vec.end());
            int res=vec[0].second;
            cout<<res<<" ";
            ++cnt[res];
            task[a].set(res);
            mp[a].insert(fa[res]);
        }
        cout<<'\n';
    }
    return 0;
}