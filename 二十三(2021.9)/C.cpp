#include <bits/stdc++.h>
using namespace std;
static unsigned long nxt = 1;
int N,S,P,T,maxcnt=-1000000000,mincnt=1000000000;
double dt,maxv=-1000000000,minv=1000000000;
vector<double> v(1005),u(1005),a(1005),b(1005),c(1005),d(1005);
vector<int> r(2005);
vector<vector<int>> edge(2005); //每个神经元或脉冲源关联的突触号
vector<int> to(1005); //每个突触到哪
vector<double> w(1005); //脉冲强度
vector<int> D(1005); //传播延迟
vector<int> cnt(1005,0); //每个神经元发放脉冲次数
vector<vector<int>> mp(100005); //每个时刻要处理的突触编号

int myrand(void) {
    nxt = nxt * 1103515245 + 12345;
    return((unsigned)(nxt/65536) % 32768);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>S>>P>>T>>dt;
    int total=0,rn;
    double rv,ru,ra,rb,rc,rd;
    while (total<N) {
        cin>>rn>>rv>>ru>>ra>>rb>>rc>>rd;
        for (int i=total;i<total+rn;++i) {
            v[i]=rv;
            u[i]=ru;
            a[i]=ra;
            b[i]=rb;
            c[i]=rc;
            d[i]=rd;
        }
        total+=rn;
    }
    for (int i=0;i<P;++i) {
        cin>>r[i+N];
    }
    int s,t;
    for (int i=0;i<S;++i) {
        cin>>s>>to[i]>>w[i]>>D[i];
        edge[s].push_back(i);
    }
    double I[1005]; //每个时刻，每个神经元接受到的脉冲量
    for (int t=1;t<=T;++t) {
        //1.检查每个脉冲源
        for (int i=N;i<N+P;++i) {
            if (r[i]>myrand()) {
                for (int it:edge[i]) {
                    if (t+D[it]<=T) {
                        mp[t+D[it]].push_back(it);
                    }
                }
            }
        }
        //2.把脉冲量加到对应神经元上
        memset(I,0,sizeof(I));
        for (int it:mp[t]) {
            I[to[it]]+=w[it];
        }
        //3.更新神经元
        for (int i=0;i<N;++i) {
            double tmpv=v[i];
            v[i]=tmpv+dt*(0.04*tmpv*tmpv+5*tmpv+140-u[i])+I[i];
            u[i]=u[i]+dt*a[i]*(b[i]*tmpv-u[i]);
            if (v[i]>=30) {
                ++cnt[i];
                for (int it:edge[i]) {
                    if (t+D[it]<=T) {
                        mp[t+D[it]].push_back(it);
                    }
                }
                v[i]=c[i];
                u[i]+=d[i];
            }
        }
    }
    for (int i=0;i<N;++i) {
        maxv=max(maxv,v[i]);
        minv=min(minv,v[i]);
        maxcnt=max(maxcnt,cnt[i]);
        mincnt=min(mincnt,cnt[i]);
    }
    cout<<fixed<<setprecision(3)<<minv<<" "<<maxv<<'\n';
    cout<<mincnt<<" "<<maxcnt;
    return 0;
}