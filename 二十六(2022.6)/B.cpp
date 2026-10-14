#include <bits/stdc++.h>
using namespace std;
int n,l,s,res=0;
vector<vector<int>> b(55,vector<int>(55));

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        size_t h1=hash<int>{}(p.first);
        size_t h2=hash<int>{}(p.second);
        return h1^(h2<<1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>l>>s;
    pair<int,int> p;
    unordered_set<pair<int,int>,PairHash> st;
    for (int i=1;i<=n;++i) {
        cin>>p.first>>p.second;
        st.insert(p);
    }
    for (int i=s;i>=0;--i) {
        for (int j=0;j<=s;++j) {
            cin>>b[i][j];
        }
    }
    for (auto it:st) {
        int x=it.first,y=it.second;
        if (x+s>l || y+s>l) {
            continue;
        }
        int flag=1;
        for (int i=0;i<=s;++i) {
            for (int j=0;j<=s;++j) {
                if ((b[i][j] && st.find({x+i,y+j})==st.end()) || (!b[i][j] && st.find({x+i,y+j})!=st.end())) {
                    flag=0;
                    break;
                }
            }
            if (!flag) {
                break;
            }
        }
        if (flag) {
            ++res;
        }
    }
    cout<<res<<'\n';
    return 0;
}