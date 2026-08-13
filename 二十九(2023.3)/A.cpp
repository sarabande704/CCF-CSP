#include <bits/stdc++.h>
using namespace std;
int n,a,b,res=0,xa,xb,ya,yb;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>a>>b;
    while (n--) {
        cin>>xa>>ya>>xb>>yb;
        if (xb<=0 || yb<=0) {
            continue;
        }
        if (xb<=a && yb<=b) {
            res+=(xb-max(xa,0))*(yb-max(ya,0));
        } else if (xb>a && yb<=b) {
            if (xa<a) {
                res+=(a-max(xa,0))*(yb-max(ya,0));
            }
        } else if (xb<=a && yb>b) {
            if (ya<b) {
                res+=(xb-max(xa,0))*(b-max(ya,0));
            }
        } else {
            if (xa<a && ya<b) {
                res+=(a-max(xa,0))*(b-max(ya,0));
            }
        }
    }
    cout<<res<<endl;
    return 0;
}