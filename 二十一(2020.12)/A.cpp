#include <bits/stdc++.h>
using namespace std;
int n,w,score,res=0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    while (n--) {
        cin>>w>>score;
        res+=w*score;
    }
    cout<<max(0,res)<<'\n';
    return 0;
}