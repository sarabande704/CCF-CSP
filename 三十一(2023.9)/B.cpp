#include <bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
int n,m,op;
double k;
vector<double> func1(100005,1),func2(100005); //拉伸和旋转操作
vector<double> pre1(100005,1),pre2(100005); //拉伸的前缀积，旋转的前缀和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) {
        cin>>op>>k;
        if (op==1) {
            func1[i]=k;
        } else {
            func2[i]=k;
        }
    }
    for (int i=1;i<=n;++i) {
        pre1[i]=func1[i]*pre1[i-1];
        pre2[i]=fmod(func2[i]+pre2[i-1],2*pi);
    }
    int i,j;
    double x,y;
    while (m--) {
        cin>>i>>j>>x>>y;
        x*=(pre1[j]/pre1[i-1]);
        y*=(pre1[j]/pre1[i-1]);
        double roll=pre2[j]-pre2[i-1];
        double newx,newy;
        newx=x*cos(roll)-y*sin(roll);
        newy=x*sin(roll)+y*cos(roll);
        cout<<fixed<<setprecision(6)<<newx<<" "<<newy<<'\n';
    }
    return 0;
}