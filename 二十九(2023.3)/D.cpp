#include <bits/stdc++.h>
using namespace std;
int n,q;

//段结构体
struct Segment {
    string l,r;
    int owner;
    bool operator<(const Segment &o) const {
        return l<o.l;
    }
};
set<Segment> segs;  //按左端点升序存储段的分配状况，段与段之间无重叠

//去掉地址串冒号，使之成为规范的十六进制串
string normalize(const string &s) {
    string res;
    for (char c:s) {
        if (c!=':') {
            res+=c;
        }
    }
    return res;
}

//给地址加一/减一
string hex_add_one(string s) {
    int carry=1;
    for (int i=s.length()-1;i>=0 && carry;--i) {
        if (s[i]=='f') {
            s[i]='0';
            carry=1;
        } else {
            if (s[i]=='9') {
                s[i]='a';
            } else {
                s[i]=s[i]+1;
            }
            carry=0;
        }
    }
    return s;
}

string hex_sub_one(string s) {
    int borrow=1;
    for (int i=s.length()-1;i>=0 && borrow;--i) {
        if (s[i]=='0') {
            s[i]='f';
            borrow=1;
        } else {
            if (s[i]=='a') {
                s[i]='9';
            } else {
                s[i]=s[i]-1;
            }
            borrow=0;
        }
    }
    return s;
}

//返回第一个可能和给定的左端点l相交的区间的迭代器
set<Segment>::iterator first_intersect(const string &l) {
    auto res=segs.lower_bound((Segment){l,"",0});
    if (res!=segs.begin()) {
        auto prev=--res;
        ++res;
        if (prev->r>=l) {
            res=prev;
        }
    }
    return res;
}

//插入新区间并合并
void insert_merge(const string &l,const string &r,int id) {
    auto it=segs.insert((Segment){l,r,id}).first;  //it为插入的元素的迭代器
    string newl=l;
    //合并
    if (it!=segs.begin()) {
        auto prev=--it;
        ++it;
        if (prev->owner==id && hex_add_one(prev->r)==l) {
            newl=prev->l;
            segs.erase(prev);
            segs.erase(it);
            it=segs.insert((Segment){newl,r,id}).first;
        }
    }
    auto nxt=++it;
    --it;
    if (nxt!=segs.end() && nxt->owner==id && hex_sub_one(nxt->l)==r) {
        string newr=nxt->r;
        segs.erase(nxt);
        segs.erase(it);
        it=segs.insert((Segment){newl,newr,id}).first;
    }
}

//分配操作
bool allocate(int id,const string &l,const string &r) {
    //检查
    bool has_empty=false,has_other=false;
    auto it=first_intersect(l);
    string cur=l;
    while (it!=segs.end() && it->l<=r) {
        if (it->owner!=id) {
            has_other=true;
            break;
        }
        if (cur<it->l) {
            has_empty=true;
        }
        cur=hex_add_one(it->r);
        ++it;
    }
    if (cur<=r) {
        has_empty=true;
    }
    if (has_other || !has_empty) {
        return false;
    }
    //分配
    vector<Segment> tmp;  //存储碎片
    it=first_intersect(l);
    while (it!=segs.end() && it->l<=r) {
        if (it->l<l) {
            tmp.push_back((Segment){it->l,hex_sub_one(l),it->owner});
        }
        if (it->r>r) {
            tmp.push_back((Segment){hex_add_one(r),it->r,it->owner});
        }
        it=segs.erase(it);  //it被自动更新为被删除元素的下一个元素的迭代器
    }
    for (auto &t:tmp) {
        segs.insert(t);
    }
    insert_merge(l,r,id);
    return true;
}

int query_point(const string &s) {
    auto it=segs.lower_bound((Segment){s,"",0});
    if (it!=segs.end() && it->l==s) {
        return it->owner;
    } else {
        if (it!=segs.begin()) {
            --it;
            if (it->r>=s) {
                return it->owner;
            }
        }
    }
    return 0;
}

int query_range(const string &l,const string &r) {
    auto it=first_intersect(l);
    if (it==segs.end() || it->l>r) {
        return 0;
    }
    string cur=l;
    int owner=-1;
    while (it!=segs.end() && it->l<=r) {
        if (cur<it->l) {
            return 0;
        }
        if (owner==-1) {
            owner=it->owner;
        } else if (owner!=it->owner) {
            return 0;
        }
        cur=hex_add_one(it->r);
        ++it;
    }
    if (cur<=r) {
        return 0;
    }
    return owner;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>q;
    int op,id;
    string s,l,r;
    while (q--) {
        cin>>op;
        if (op==1) {
            cin>>id>>l>>r;
            l=normalize(l);
            r=normalize(r);
            bool tmp=allocate(id,l,r);
            if (tmp) {
                cout<<"YES\n";
            } else {
                cout<<"NO\n";
            }
        } else if (op==2) {
            cin>>s;
            s=normalize(s);
            cout<<query_point(s)<<'\n';
        } else {
            cin>>l>>r;
            l=normalize(l);
            r=normalize(r);
            cout<<query_range(l,r)<<'\n';
        }
    }
    return 0;
}