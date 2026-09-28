#include <bits/stdc++.h>
using namespace std;
int n;
vector<string> state;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    string str,s;
    for (int i=0;i<n;++i) {
        for (int j=0;j<8;++j) {
            cin>>s;
            str+=s;
        }
        state.push_back(str);
        int cnt=1;
        for (int j=0;j<i;++j) {
            if (state[j]==str) {
                ++cnt;
            }
        }
        str="";
        cout<<cnt<<'\n';
    }
    return 0;
}