#include <bits/stdc++.h>
using namespace std;
int n,r,m,p;

struct Person {
    int d,u,r;
    bool operator==(const Person &o) const {
        return d==o.d && u==o.u && r==o.r;
    }
};

struct PersonHash {
    size_t operator()(const Person &p) const {
        size_t h1=hash<int>{}(p.u);
        size_t h2=hash<int>{}(p.r);
        return h1^(h2<<1);
    }
};
unordered_map<int,pair<int,int>> mp; //每个地区的风险区间
vector<unordered_set<Person,PersonHash>> info(7); //七日内收到的风险信息
int pos=0; //从0号位开始存储info
set<int> s; //当日风险名单

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for (int i=0;i<n;++i) {
        s.clear();
        cin>>r>>m;
        while (r--) {
            cin>>p;
            auto it=mp.find(p);
            if (it==mp.end() || i>it->second.second+1) {
                mp[p]={i,i+6};
            } else {
                it->second.second=i+6;
            }
        }
        Person ps;
        while (m--) {
            cin>>ps.d>>ps.u>>ps.r;
            if (ps.d>i-7 && mp.find(ps.r)!=mp.end() && mp[ps.r].first<=ps.d && mp[ps.r].second>=i) {
                s.insert(ps.u);
                info[pos].insert(ps);
            }
        }
        for (int j=(pos+1)%7;j!=pos;j=(j+1)%7) {
            for (auto it=info[j].begin();it!=info[j].end();) {
                if (it->d>i-7 && mp.find(it->r)!=mp.end() && mp[it->r].first<=it->d && mp[it->r].second>=i) {
                    s.insert(it->u);
                    ++it;
                } else {
                    it=info[j].erase(it);
                }
            }
        }
        pos=(pos+1)%7;
        cout<<i<<" ";
        for (int p:s) {
            cout<<p<<" ";
        }
        cout<<'\n';
    }
    return 0;
}