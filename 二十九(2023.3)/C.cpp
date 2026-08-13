#include <bits/stdc++.h>
using namespace std;
int n,m,DN[2501],num,attr,val;
unordered_map<int,unordered_map<int,bitset<2501>>> user;  //存储属性的不同值下的用户
unordered_map<int,bitset<2501>> mp;  //存储一个属性下所有用户

bitset<2501> func() {
    bitset<2501> s;
    char ch;
    cin>>ch;
    if (ch>='0' && ch<='9') {
        cin.putback(ch);
        int x,y;
        char op;
        cin>>x>>op>>y;
        if (op==':') {
            return user[x][y];
        } else {
            return mp[x]&(~user[x][y]);
        }
    }
    if (ch=='&') {
        cin>>ch;
        bitset<2501> s1=func();
        cin>>ch;
        cin>>ch;
        bitset<2501> s2=func();
        cin>>ch;
        return s1&s2;
    } else if (ch=='|') {
        cin>>ch;
        bitset<2501> s1=func();
        cin>>ch;
        cin>>ch;
        bitset<2501> s2=func();
        cin>>ch;
        return s1|s2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    for (int i=1;i<=n;++i) {
        cin>>DN[i]>>num;
        while (num--) {
            cin>>attr>>val;
            user[attr][val].set(i);
            mp[attr].set(i);
        }
    }
    cin>>m;
    while (m--) {
        bitset<2501> s=func();
        set<int> res;
        for (int i=1;i<=n;++i) {
            if (s.test(i)) {
                res.insert(DN[i]);
            }
        }
        for (auto &it:res) {
            cout<<it<<" ";
        }
        cout<<'\n';
    }
    return 0;
}