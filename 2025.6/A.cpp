#include <bits/stdc++.h>
using namespace std;
int k,a,b,n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>k;
    while (k--) {
        cin>>a>>b>>n;
        cout<<((n-a)*(100/b))/10+1<<" "<<((n-a)*(100/b))%10+1<<'\n';
    }
    return 0;
}