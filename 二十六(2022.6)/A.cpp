#include <bits/stdc++.h>
using namespace std;
int n,total=0;
vector<int> a(1005);

int main() {
    cin>>n;
    for (int i=1;i<=n;++i) {
        cin>>a[i];
        total+=a[i];
    }
    double avg=(total*1.0)/n;
    double d;
    for (int i=1;i<=n;++i) {
        d+=(a[i]-avg)*(a[i]-avg);
    }
    d/=n;
    d=sqrt(d);
    for (int i=1;i<=n;++i) {
        double res=(a[i]-avg)/d;
        printf("%f\n",res);
    }
    return 0;
}