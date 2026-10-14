#include <bits/stdc++.h>
using namespace std;
int n,m,q,cnt=0;
unordered_map<string,int> mp; //存储每个角色名的编号
unordered_map<int,unordered_set<string>> cate; //存储每个角色的资源种类
unordered_map<int,unordered_set<string>> name; //存储每个角色的资源名称
unordered_map<int,unordered_set<string>> op; //存储每个角色的操作
unordered_map<string,bitset<505>> user; //存储每个用户名关联到的角色
unordered_map<string,bitset<505>> group; //存储每个用户组关联到的角色

void init() {
    cin>>n>>m>>q;
    string str,tmp;
    int nv,no,nn;
    for (int i=1;i<=n;++i) {
        cin>>str;
        mp[str]=++cnt;
        cin>>nv;
        while (nv--) {
            cin>>tmp;
            op[cnt].insert(tmp);
        }
        cin>>no;
        while (no--) {
            cin>>tmp;
            cate[cnt].insert(tmp);
        }
        cin>>nn;
        while (nn--) {
            cin>>tmp;
            name[cnt].insert(tmp);
        }
    }
    int ns;
    for (int i=1;i<=m;++i) {
        cin>>str>>ns;
        int id=mp[str];
        while (ns--) {
            cin>>tmp;
            if (tmp=="u") {
                cin>>tmp;
                user[tmp].set(id);
            } else {
                cin>>tmp;
                group[tmp].set(id);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    init();
    string str,s1,s2,s3;
    int ng;
    while (q--) {
        int flag=0;
        cin>>str>>ng;
        bitset<505> bt; //用户关联的角色
        bt|=user[str];
        while (ng--) {
            cin>>str;
            bt|=group[str];
        }
        cin>>s1>>s2>>s3;
        for (int i=1;i<=n;++i) {
            if (!bt.test(i)) {
                continue;
            }
            if (op[i].find(s1)==op[i].end() && op[i].find("*")==op[i].end()) {
                continue;
            }
            if (cate[i].find(s2)==cate[i].end() && cate[i].find("*")==cate[i].end()) {
                continue;
            }
            if (name[i].find(s3)==name[i].end() && !name[i].empty()) {
                continue;
            }
            flag=1;
            cout<<1<<'\n';
            break;
        }
        if (!flag) {
            cout<<0<<'\n';
        }
    }
    return 0;
}