#include <bits/stdc++.h>
using namespace std;
int n,m,t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m>>t;
    vector<int> vec(n*m);
    for (int i=0;i<n*m;++i) {
        cin>>vec[i];
    } 
    int op,p,q,col=m;
    while (t--) {
        cin>>op>>p>>q;
        if (op==1) {
            col=q;
        } else if (op==2) {
            vector<int> newvec;
            for (int i=0;i<col;++i) {
                for (int j=0;i+j<n*m;j+=col) {
                    newvec.push_back(vec[i+j]);
                }
            }
            vec=newvec;
            col=m*n/col;
        } else {
            cout<<vec[p*col+q]<<endl;
        }
    }
    return 0;
}