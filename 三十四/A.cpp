#include <bits/stdc++.h>
using namespace std;
int n,m,p,q;

int main() {
    cin>>n>>m>>p>>q;
    int num;
    vector<int> vec;
    for (int i=1;i<=n*m;++i) {
        cin>>num;
        vec.push_back(num);
    }
    for (int j=0;j<p;++j) {
        for (int k=0;k<q;++k) {
            cout<<vec[j*q+k]<<" ";
        }
        cout<<endl;
    }
    return 0;
}