#include <bits/stdc++.h>
using namespace std;
int n;
double i;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    scanf("%d%lf",&n,&i);
    vector<double> money(n+1);
    double x;
    for (int k=0;k<=n;++k) {
        scanf("%lf", &x);
        money[k]=x;
        if (k) {
            for (int j=1;j<=k;++j) {
                money[k]/=(1+i);
            }
        }
    }
    x=0;
    for (int k=0;k<=n;++k) {
        x+=money[k];
    }
    printf("%lf", x);
    return 0;
}