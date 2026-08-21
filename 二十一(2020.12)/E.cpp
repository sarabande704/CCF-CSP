#include <bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
int n,m;
vector<int> pos;  //存储左端点和右端点+1

//操作
struct func {
    int op;
    int l,r;
    long long a,b,c,k;
};
vector<func> vec(40005);

struct Node {
    int left,right;  //离散化后的端点
    long long sx=0,sy=0,sz=0;
    long long multag=1;
    long long addx=0,addy=0,addz=0;
    int roll=0;
};

void pushup(vector<Node> &tr,int root) {
    tr[root].sx=(tr[root*2].sx+tr[root*2+1].sx)%mod;
    tr[root].sy=(tr[root*2].sy+tr[root*2+1].sy)%mod;
    tr[root].sz=(tr[root*2].sz+tr[root*2+1].sz)%mod;
}

void maketag1(vector<Node> &tr,int root,long long mul) {
    tr[root].multag=(tr[root].multag*mul)%mod;
    tr[root].addx=(tr[root].addx*mul)%mod;
    tr[root].addy=(tr[root].addy*mul)%mod;
    tr[root].addz=(tr[root].addz*mul)%mod;
    tr[root].sx=(tr[root].sx*mul)%mod;
    tr[root].sy=(tr[root].sy*mul)%mod;
    tr[root].sz=(tr[root].sz*mul)%mod;
}

void maketag2(vector<Node> &tr,int root,long long a,long long b,long long c) {
    int l=tr[root].left,r=tr[root].right;
    long long len=pos[r]-pos[l-1];  
    tr[root].addx=(tr[root].addx+a)%mod;
    tr[root].addy=(tr[root].addy+b)%mod;
    tr[root].addz=(tr[root].addz+c)%mod;
    tr[root].sx=(tr[root].sx+a*len%mod)%mod;
    tr[root].sy=(tr[root].sy+b*len%mod)%mod;
    tr[root].sz=(tr[root].sz+c*len%mod)%mod;
}

void maketag3(vector<Node> &tr,int root,int k) {
    if (k==1) {
        swap(tr[root].sx,tr[root].sy);
        swap(tr[root].sy,tr[root].sz);
        swap(tr[root].addx,tr[root].addy);
        swap(tr[root].addy,tr[root].addz);
    } else if (k==2) {
        swap(tr[root].sx,tr[root].sz);
        swap(tr[root].sy,tr[root].sz);
        swap(tr[root].addx,tr[root].addz);
        swap(tr[root].addy,tr[root].addz);
    }
    tr[root].roll=(tr[root].roll+k)%3;
}

void pushdown(vector<Node> &tr,int root) {
    maketag1(tr,root*2,tr[root].multag);
    maketag3(tr,root*2,tr[root].roll);
    maketag2(tr,root*2,tr[root].addx,tr[root].addy,tr[root].addz);
    maketag1(tr,root*2+1,tr[root].multag);
    maketag3(tr,root*2+1,tr[root].roll);
    maketag2(tr,root*2+1,tr[root].addx,tr[root].addy,tr[root].addz);
    tr[root].multag=1;
    tr[root].addx=tr[root].addy=tr[root].addz=tr[root].roll=0;
}

void build(vector<Node> &tr,int l,int r,int root) {
    tr[root].left=l;
    tr[root].right=r;
    if (l==r) {
        return;
    }
    int mid=(l+r)>>1;
    build(tr,l,mid,root*2);
    build(tr,mid+1,r,root*2+1);
    pushup(tr,root);
}

void update1(vector<Node> &tr,int x,int y,int root,long long k) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        maketag1(tr,root,k);
    } else {
        pushdown(tr,root);
        int mid=(l+r)>>1;
        if (x<=mid) {
            update1(tr,x,y,root*2,k);
        }
        if (y>mid) {
            update1(tr,x,y,root*2+1,k);
        }
        pushup(tr,root);
    }
}

void update2(vector<Node> &tr,int x,int y,int root,long long a,long long b,long long c) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        maketag2(tr,root,a,b,c);
    } else {
        pushdown(tr,root);
        int mid=(l+r)>>1;
        if (x<=mid) {
            update2(tr,x,y,root*2,a,b,c);
        }
        if (y>mid) {
            update2(tr,x,y,root*2+1,a,b,c);
        }
        pushup(tr,root);
    }
}

void update3(vector<Node> &tr,int x,int y,int root) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        maketag3(tr,root,1);
    } else {
        pushdown(tr,root);
        int mid=(l+r)>>1;
        if (x<=mid) {
            update3(tr,x,y,root*2);
        }
        if (y>mid) {
            update3(tr,x,y,root*2+1);
        }
        pushup(tr,root);
    }
}

long long query1(vector<Node> &tr,int x,int y,int root) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        return tr[root].sx%mod;
    }
    long long res=0;
    int mid=(l+r)>>1;
    pushdown(tr,root);
    if (x<=mid) {
        res=(res+query1(tr,x,y,root*2))%mod;
    }
    if (y>mid) {
        res=(res+query1(tr,x,y,root*2+1))%mod;
    }
    return res%mod;
}

long long query2(vector<Node> &tr,int x,int y,int root) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        return tr[root].sy%mod;
    }
    long long res=0;
    int mid=(l+r)>>1;
    pushdown(tr,root);
    if (x<=mid) {
        res=(res+query2(tr,x,y,root*2))%mod;
    }
    if (y>mid) {
        res=(res+query2(tr,x,y,root*2+1))%mod;
    }
    return res%mod;
}

long long query3(vector<Node> &tr,int x,int y,int root) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        return tr[root].sz%mod;
    }
    long long res=0;
    int mid=(l+r)>>1;
    pushdown(tr,root);
    if (x<=mid) {
        res=(res+query3(tr,x,y,root*2))%mod;
    }
    if (y>mid) {
        res=(res+query3(tr,x,y,root*2+1))%mod;
    }
    return res%mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=m;++i) {
        cin>>vec[i].op>>vec[i].l>>vec[i].r;
        pos.push_back(vec[i].l);
        pos.push_back(vec[i].r+1);
        if (vec[i].op==1) {
            cin>>vec[i].a>>vec[i].b>>vec[i].c;
        } else if (vec[i].op==2) {
            cin>>vec[i].k;
        }
    }
    //离散化
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    unordered_map<int,int> mp;  //存储从原始端点值到离散后的值的映射
    for (int i=0;i<pos.size();++i) {
        mp[pos[i]]=i+1;
    }
    vector<Node> tr(4e5);
    build(tr,1,pos.size()-1,1);
    for (int i=1;i<=m;++i) {
        int op=vec[i].op,l=mp[vec[i].l],r=mp[vec[i].r+1]-1;
        if (op==1) {
            long long a=vec[i].a,b=vec[i].b,c=vec[i].c;
            update2(tr,l,r,1,a,b,c);
        } else if (op==2) {
            long long k=vec[i].k;
            update1(tr,l,r,1,k);
        } else if (op==3) {
            update3(tr,l,r,1);
        } else {
            long long tmp1=query1(tr,l,r,1),tmp2=query2(tr,l,r,1),tmp3=query3(tr,l,r,1);
            long long res=(tmp1*tmp1%mod+tmp2*tmp2%mod+tmp3*tmp3%mod)%mod;
            cout<<res<<'\n';
        }
    }
    return 0;
}