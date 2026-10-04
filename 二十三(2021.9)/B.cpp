#include <bits/stdc++.h>
using namespace std;
int n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    vector<int> A(n+1,0);
    vector<vector<int>> pos(10005); //存储等于某个值的元素的所有位置
    for (int i=1;i<=n;++i) {
        cin>>A[i];
        pos[A[i]].push_back(i);
    }
    int res=0,pre=0;
    vector<int> tmpA(n+2,0);
    for (int p=10000;p>=1;--p) {
        for (int id:pos[p]) {
            tmpA[id]=A[id];
            if (!tmpA[id-1] && !tmpA[id+1]) {
                ++pre;
            } else if (tmpA[id-1] && tmpA[id+1]) {
                --pre;
            }
        }
        res=max(res,pre);
    }
    cout<<res<<'\n';
    return 0;
}