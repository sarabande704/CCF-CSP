#include <bits/stdc++.h>
using namespace std;
const double pi=acos(-1);
int n,T;
vector<vector<int>> Q(8,vector<int>(8,0));

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    //1.读入量化矩阵Q
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j) {
            cin>>Q[i][j];
        }
    }
    //2.初始化矩阵M
    vector<vector<int>> M(8,vector<int>(8,0));
    //3.读入扫描数据
    cin>>n>>T;
    int cnt=0; //已经读入的数据数量
    int flag=0;
    for (int i=0;i<=14;++i) {
        if (i%2) {
            for (int j=min(i,7);j>=0 && (i-j)<=7;--j) {
                cin>>M[i-j][j];
                ++cnt;
                if (cnt==n) {
                    flag=1;
                    break;
                }
            }
        } else {
            for (int j=min(i,7);j>=0 && (i-j)<=7;--j) {
                cin>>M[j][i-j];
                ++cnt;
                if (cnt==n) {
                    flag=1;
                    break;
                }
            }
        }
        if (flag) {
            break;
        }
    }
    if (T==0) {
        for (int i=0;i<8;++i) {
            for (int j=0;j<8;++j) {
                cout<<M[i][j]<<" ";
            }
            cout<<'\n';
        }
        return 0;
    }
    //4.量化
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j)  {
            M[i][j]*=Q[i][j];
        }
    }
    if (T==1) {
        for (int i=0;i<8;++i) {
            for (int j=0;j<8;++j) {
                cout<<M[i][j]<<" ";
            }
            cout<<'\n';
        }
        return 0;
    }
    //5.进行离散余弦逆变换
    vector<vector<double>> newM(8,vector<double>(8,0));
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j) {
            for (int u=0;u<8;++u) {
                for (int v=0;v<8;++v) {
                    newM[i][j]+=M[u][v]*cos(pi/8*(i+0.5)*u)*cos(pi/8*(j+0.5)*v)*(u==0 ? sqrt(0.5) : 1)*(v==0 ? sqrt(0.5) : 1);
                }
            }
            newM[i][j]/=4;
        }
    }
    //6.舍入
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j) {
            newM[i][j]+=128;
            newM[i][j]=round(newM[i][j]);
            if (newM[i][j]>255) {
                newM[i][j]=255;
            } else if (newM[i][j]<0) {
                newM[i][j]=0;
            }
        }
    }
    for (int i=0;i<8;++i) {
        for (int j=0;j<8;++j) {
            cout<<newM[i][j]<<" ";
        }
        cout<<'\n';
    }
    return 0;
}