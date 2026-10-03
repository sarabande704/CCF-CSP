#include <bits/stdc++.h>
using namespace std;
const long long mod=1000000007;
int n,m;
string line; //待处理的后缀表达式

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    cin.ignore();
    getline(cin,line);
    istringstream iss(line);
    vector<string> vecstr; //存储后缀表达式的各个元素
    string w;
    while (iss>>w) {
        vecstr.push_back(w);
    }
    int id;
    vector<long long> val(n+1);
    while (m--) {
        cin>>id;
        for (int i=1;i<=n;++i) {
            cin>>val[i];
        }
        vector<long long> origin; //表达式不求导的值
        vector<long long> derive; //表达式求导后的值
        stack<int> st; //存储表达式的编号
        int pos=0; //表达式编号
        for (string str:vecstr) {
            if (str[0]=='x') {
                string tmps=str.substr(1);
                int tmp=stoi(tmps); //自变量的下标
                origin.push_back((val[tmp]%mod+mod)%mod);
                if (tmp==id) {
                    derive.push_back(1);
                } else {
                    derive.push_back(0);
                }
            } else if (str=="+") {
                int t1=st.top();
                st.pop();
                int t2=st.top();
                st.pop();
                origin.push_back(((origin[t1]+origin[t2])%mod+mod)%mod);
                derive.push_back(((derive[t1]+derive[t2])%mod+mod)%mod);
            } else if (str=="-") {
                int t1=st.top();
                st.pop();
                int t2=st.top();
                st.pop();
                origin.push_back(((origin[t2]-origin[t1])%mod+mod)%mod);
                derive.push_back(((derive[t2]-derive[t1])%mod+mod)%mod);
            } else if (str=="*") {
                int t1=st.top();
                st.pop();
                int t2=st.top();
                st.pop();
                origin.push_back((origin[t1]*origin[t2]%mod+mod)+mod);
                derive.push_back(((origin[t1]*derive[t2]+origin[t2]*derive[t1])%mod+mod)%mod);
            } else {
                origin.push_back(stoi(str));
                derive.push_back(0);
            }
            st.push(pos);
            ++pos;
        }
        cout<<derive[st.top()]<<'\n';
    }
    return 0;
}