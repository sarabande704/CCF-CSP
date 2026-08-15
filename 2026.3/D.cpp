#include <bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5;
int n,m,ll,rr,op;
long long k,v,a[MAXN],inv2;

struct Node {
    int left,right;
    long long A0;  //第0位的和
    long long Q0;  //第0位的平方和
    long long At[12];  //第t位(t>=1)和
    long long Ct[12];
    long long tag[12];
    Node() {
        A0=Q0=0;
        memset(At,0,sizeof(At));
        memset(Ct,0,sizeof(Ct));
        memset(tag,0,sizeof(tag));
    }
};
Node tr[MAXN*4];

void pushup(int root) {
    tr[root].A0=(tr[root*2].A0+tr[root*2+1].A0)%k;
    tr[root].Q0=(tr[root*2].Q0+tr[root*2+1].Q0)%k;
    for (int i=1;i<=11;++i) {
        tr[root].At[i]=(tr[root*2].At[i]+tr[root*2+1].At[i])%k;
        tr[root].Ct[i]=(tr[root*2].Ct[i]+tr[root*2+1].Ct[i])%k;
    }
}

void pushdown(int root) {
    long long v0=tr[root].tag[0],a1=tr[root*2].A0,a2=tr[root*2+1].A0;
    if (v0) {
        tr[root*2].Q0=(tr[root*2].Q0+2*v0%k*tr[root*2].A0%k+(tr[root*2].right-tr[root*2].left+1)*v0%k*v0%k)%k;
        tr[root*2].A0=(tr[root*2].A0+(tr[root*2].right-tr[root*2].left+1)*v0%k)%k;
        tr[root*2+1].Q0=(tr[root*2+1].Q0+2*v0%k*tr[root*2+1].A0%k+(tr[root*2+1].right-tr[root*2+1].left+1)*v0%k*v0%k)%k;
        tr[root*2+1].A0=(tr[root*2+1].A0+(tr[root*2+1].right-tr[root*2+1].left+1)*v0%k)%k;
        tr[root*2].tag[0]=(tr[root*2].tag[0]+v0)%k;
        tr[root*2+1].tag[0]=(tr[root*2+1].tag[0]+v0)%k;
    }
    for (int i=1;i<=11;++i) {
        long long vt=tr[root].tag[i];
        tr[root*2].Ct[i]=(tr[root*2].Ct[i]+v0*tr[root*2].At[i]%k+vt*(a1+(tr[root*2].right-tr[root*2].left+1))%k+(tr[root*2].right-tr[root*2].left+1)*vt%k*v0%k)%k;
        tr[root*2].At[i]=(tr[root*2].At[i]+(tr[root*2].right-tr[root*2].left+1)*vt%k)%k;
        tr[root*2+1].Ct[i]=(tr[root*2+1].Ct[i]+v0*tr[root*2+1].At[i]%k+vt*(a2+(tr[root*2+1].right-tr[root*2+1].left+1))%k+(tr[root*2+1].right-tr[root*2+1].left+1)*vt%k*v0%k)%k;
        tr[root*2+1].At[i]=(tr[root*2+1].At[i]+(tr[root*2+1].right-tr[root*2+1].left+1)*vt%k)%k;
        tr[root*2].tag[i]=(tr[root*2].tag[i]+vt)%k;
        tr[root*2+1].tag[i]=(tr[root*2+1].tag[i]+vt)%k;
    }
    memset(tr[root].tag,0,sizeof(tr[root].tag));
}

void build(int l,int r,int root) {
    tr[root].left=l;
    tr[root].right=r;
    if (l==r) {
        long long tmp=a[l];
        tr[root].A0=tmp%k;
        tr[root].Q0=(tr[root].A0*tr[root].A0)%k;
        tmp/=k;
        for (int i=1;i<=11;++i) {
            if (!tmp) {
                break;
            }
            tr[root].At[i]=tmp%k;
            tr[root].Ct[i]=tr[root].At[i]*(tr[root].A0+1)%k;
            tmp/=k;
        }
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,root*2);
    build(mid+1,r,root*2+1);
    pushup(root);
}

void update(int root,int x,int y,vector<long long> &vbit) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        long long v0=vbit[0],a1=tr[root].A0;
        if (v0) {
            tr[root].Q0=(tr[root].Q0+2*v0%k*tr[root].A0%k+(tr[root].right-tr[root].left+1)*v0%k*v0%k)%k;
            tr[root].A0=(tr[root].A0+(tr[root].right-tr[root].left+1)*v0%k)%k;
            tr[root].tag[0]=(tr[root].tag[0]+v0)%k;
        }
        for (int i=1;i<vbit.size();++i) {
            long long vt=vbit[i];
            tr[root].Ct[i]=(tr[root].Ct[i]+v0*tr[root].At[i]%k+vt*(a1+(tr[root].right-tr[root].left+1))%k+(tr[root].right-tr[root].left+1)*vt%k*v0%k)%k;
            tr[root].At[i]=(tr[root].At[i]+(tr[root].right-tr[root].left+1)*vt%k)%k;
            tr[root].tag[i]=(tr[root].tag[i]+vt)%k;
        }
    } else {
        int mid=(l+r)>>1;
        pushdown(root);
        if (x<=mid) {
            update(root*2,x,y,vbit);
        }
        if (y>mid) {
            update(root*2+1,x,y,vbit);
        }
        pushup(root);
    }
}

void query(int x,int y,int root,vector<long long> &resbit) {
    int l=tr[root].left,r=tr[root].right;
    if (x<=l && y>=r) {
        resbit[0]=(resbit[0]+(tr[root].A0+tr[root].Q0)%k*inv2)%k;
        for (int i=1;i<=11;++i) {
            resbit[i]=(resbit[i]+tr[root].Ct[i])%k;
        }
        return;
    }
    int mid=(l+r)>>1;
    pushdown(root);
    if (x<=mid) {
        query(x,y,root*2,resbit);
    }
    if (y>mid) {
        query(x,y,root*2+1,resbit);
    }
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>m>>k;
    inv2=(k+1)/2;
	for (int i=1;i<=n;++i) {
		cin>>a[i];
	}
    build(1,n,1);
    while (m--) {
        cin>>op;
        if (op==1) {
            cin>>ll>>rr>>v;
            vector<long long> vbit;
            if (!v) {
                vbit.push_back(0);
            } else {
                while (v) {
                    vbit.push_back(v%k);
                    v/=k;
                }
                int len=vbit.size();
                while (len<12) {
                    vbit.push_back(0);
                    ++len;
                }
            }
            update(1,ll,rr,vbit);
        } else {
            cin>>ll>>rr;
            vector<long long> resbit(12,0);
            query(ll,rr,1,resbit);
            long long res=0;
            for (int i=11;i>=0;--i) {
                res*=k;
                res+=resbit[i];
            }
            cout<<res<<'\n';
        }
    }
	return 0;
}