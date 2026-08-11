#include <bits/stdc++.h>
using namespace std;
int n,m,cnt=0;
string s;
unordered_set<string> a,b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    while (n--) {
        cin>>s;
        for (auto &ch:s) {
            ch=tolower(ch);
        }
        a.insert(s);
    }
    while (m--) {
        cin>>s;
        for (auto &ch:s) {
            ch=tolower(ch);
        }
        if (b.find(s)==b.end()) {
            b.insert(s);
            if (a.find(s)!=a.end()) {
                ++cnt;
            }
        }
    }
    cout<<cnt<<'\n'<<a.size()+b.size()-cnt<<'\n';
    return 0;
}