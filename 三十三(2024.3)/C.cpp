#include <bits/stdc++.h>
using namespace std;
const double eps=1e-8;
int n,m,i,j,k,row,col;
string s;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    while (n--) {
        cin>>m;  //物质数量
        unordered_set<string> ele;  //存储不同元素
        vector<unordered_map<string,int>> mp(m);  //存储不同物质各自含有的元素的数量
        for (i=0;i<m;++i) {
            cin>>s;  //物质
            string tmp="";  //元素
            for (j=0;j<s.length();) {
                if (s[j]>='0' && s[j]<='9') {
                    ele.insert(tmp);
                    int total=s[j]-'0';
                    for (k=j+1;k<s.length();++k) {
                        if (s[k]>='0' && s[k]<='9') {
                            total=total*10+s[k]-'0';
                        } else {
                            mp[i][tmp]=total;
                            tmp="";
                            j=k;
                            break;
                        }
                    }
                    if (k==s.length()) {
                        mp[i][tmp]=total;
                        break;
                    }
                } else {
                    tmp+=s[j];
                    ++j;
                }
            }
        }
        vector<vector<double>> vec(ele.size(),vector<double>(m,0.0));  //矩阵
        //初始化矩阵
        int cnt=-1;  //遍历到第几个元素
        for (auto it:ele) {
            ++cnt;
            for (i=0;i<m;++i) {
                vec[cnt][i]=(double)mp[i][it];
            }
        }
        //高斯消元
        row=col=0;
        while (1) {
            double tmp=vec[row][col];
            j=row;
            if (abs(tmp-0.0)<eps) {
                for (j=row+1;j<=cnt;++j) {
                    if (abs(vec[j][col]-0.0)>=eps) {
                        swap(vec[row],vec[j]);
                        break;
                    }
                }
                if (j>cnt) {
                    ++col;
                    if (col>=m) {
                        break;
                    }
                    continue;  //当前列全是0，直接到下一列
                }
            }
            //消元
            for (j=j+1;j<=cnt;++j) {
                if (abs(vec[j][col]-0.0)>=eps) {
                    double mul=vec[j][col]*(-1)/vec[row][col];
                    for (k=col;k<m;++k) {
                        vec[j][k]+=vec[row][k]*mul;
                    }
                }
            }
            ++row;
            ++col;
            if (row>cnt || col>=m) {
                break;
            }
        }
        //求秩
        int r=0;
        for (i=0;i<=cnt;++i) {
            for (j=0;j<m;++j) {
                if (abs(vec[i][j]-0.0)>=eps) {
                    ++r;
                    break;
                } 
            }
        }
        if (r<m) {
            cout<<"Y\n";
        } else {
            cout<<"N\n";
        }
    }
    return 0;
}