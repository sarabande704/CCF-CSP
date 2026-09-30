#include <bits/stdc++.h>
using namespace std;
const long double eps=1e-15;
int n,m,k;
vector<string> res(25);

bool cmp1(long long a,long long b,long long c,int op) {
    if (op==1) {
        return ((long long)m*1000000-1000*a)*((long long)m*1000000-1000*a)>=c*c*b;
    } else {
        return ((long long)m*1000000-1000*a)*((long long)m*1000000-1000*a)<=c*c*b;
    }
}

bool cmp2(long long a,long long b,long long c,long long d) {
    return (2000*(1000*(long long)m-a))*(2000*(1000*(long long)m-a))<=(c+d)*(c+d)*b;
}

bool bigger(long double a,long double b) {
    return a>b+eps || fabs(a-b)<eps;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>k;
    //法一：化成整数
    /**************************************************************
    long long l1=0,l2=0; //分别存平均耗时、标准差放大1000倍后的和/平方
    vector<long long> x(25); //存放大1000倍的x
    double d=0;
    for (int i=1;i<=n;++i) {
        cin>>d;
        l1+=(long long)(d*1000);
    }
    for (int i=1;i<=n;++i) {
        cin>>d;
        l2+=(long long)(d*1000)*(long long)(d*1000);
    }
    for (int i=1;i<=k;++i) {
        cin>>d;
        x[i]=(long long)(d*1000);
    }
    for (int i=1;i<=k;++i) {
        cin>>res[i];
    }
    for (int i=1;i<k;++i) {
        if (cmp1(l1,l2,x[i],1) && cmp1(l1,l2,x[i+1],2)) {
            if (cmp2(l1,l2,x[i],x[i+1])) {
                cout<<res[i]<<'\n';
            } else {
                cout<<res[i+1]<<'\n';
            }
            break;
        }
    }
    *************************************************************/
   //法二：实数运算
    long double d1=0,d2=0,d; //存储总平均耗时、总标准差
    vector<long double> x(25);
    for (int i=1;i<=n;++i) {
        cin>>d;
        d1+=d;
    }
    for (int i=1;i<=n;++i) {
        cin>>d;
        d2+=d*d;
    }
    d2=sqrtl(d2);
    for (int i=1;i<=k;++i) {
        cin>>x[i];
    }
    for (int i=1;i<=k;++i) {
        cin>>res[i];
    }
    long double tmpd=((long double)m-d1)/d2;
    for (int i=1;i<k;++i) {
        if (bigger(tmpd,x[i]) && bigger(x[i+1],tmpd)) {
            if (bigger(x[i+1]-tmpd,tmpd-x[i])) {
                cout<<res[i]<<'\n';
            } else {
                cout<<res[i+1]<<'\n';
            }
            break;
        }
    }
    return 0;
}