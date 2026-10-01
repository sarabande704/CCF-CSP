#include <bits/stdc++.h>
using namespace std;
const long long m=929;
int w,s;
int state=0; //编码器状态，大写0，小写1，数字2
string str;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>w>>s;
    cin>>str;
    //第一步：生成数字序列
    vector<long long> vec; //由字符串生成的数字序列
    for (int i=0;i<str.length();++i) {
        char ch=str[i];
        if (ch>='A' && ch<='Z') {
            if (state==1) {
                vec.push_back(28);
                vec.push_back(28);
            } else if (state==2) {
                vec.push_back(28);
            }
            vec.push_back(ch-'A');
            state=0;
        } else if (ch>='a' && ch<='z') {
            if (state!=1) {
                vec.push_back(27);
            }
            vec.push_back(ch-'a');
            state=1;
        } else {
            if (state!=2) {
                vec.push_back(28);
            }
            vec.push_back(ch-'0');
            state=2;
        }
    }
    if (vec.size()%2) {
        vec.push_back(29);
    }
    //第二步：生成编码
    vector<long long> code; //编码
    for (int i=0;i<=vec.size()-2;i+=2) {
        code.push_back(30*vec[i]+vec[i+1]);
    }
    //第三步：确定长度
    int k=0; //校验码的长度
    if (s!=-1) {
        k=1<<(s+1);
    }
    int len=1+code.size()+k; //除了填充码字外的总数
    int x=(len%w) ? w-(len%w) : 0; //填充码字的数量
    len+=x;
    len-=k;
    code.insert(code.begin(),len);
    for (int i=1;i<=x;++i) {
        code.push_back(900);
    }
    //第四步：求校验位
    vector<long long> qpow(520,0); //-(3的幂次)
    qpow[1]=-3;
    for (int i=2;i<=512;++i) {
        qpow[i]=(qpow[i-1]*3%m+m)%m;
    }
    if (k) {
        int n=code.size(); //全部数据码字的数量
        vector<long long> d(k+n,0),q(n,0),g(k+1,0),tmpg(k+1,0),r(k,0); //多项式系数
        for (int i=k;i<=k+n-1;++i) {
            d[i]=code[n+k-i-1]%m;
        }
        g[0]=1;
        for (int i=1;i<=k;++i) {
            for (int j=0;j<=k;++j) {
                tmpg[j]=0;
            }
            for (int j=0;j<=i-1;++j) {
                if (g[j]) {
                    tmpg[j+1]=g[j];
                    g[j]=(g[j]*qpow[i]%m+m)%m;
                }
            }
            for (int j=0;j<=i;++j) {
                g[j]=((g[j]+tmpg[j])%m+m)%m;
            }
        }
        for (int i=k+n-1;i>=k;--i) {
            long long a=d[i];
            for (int j=k-1;j>=0;--j) {
                if (i-j<n) {
                    a=((a-q[i-j]*g[j])%m+m)%m;
                } else {
                    break;
                }
            }
            q[i-k]=a;
        }
        for (int i=0;i<=k-1;++i) {
            long long a=0;
            for (int j=0;j<=min(n-1,i);++j) {
                a=((a+q[j]*g[i-j])%m+m)%m;
            }
            r[i]=a;
        }
        for (int i=k-1;i>=0;--i) {
            code.push_back(r[i]);
        }
    }
    //输出结果
    for (long long res:code) {
        cout<<res<<'\n';
    }
    return 0;
}