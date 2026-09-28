#include <bits/stdc++.h>
using namespace std;
int s;
string txt; //解压缩后的数据

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>s;
    string str;
    char ch;
    //读取引导域
    while (1) {
        cin>>ch;
        str+=ch;
        cin>>ch;
        str+=ch;
        --s;
        int x=stoi(str,nullptr,16);
        str="";
        if ((x&128)==0) {
            break;
        }
    }
    while (s) {
        //读取基本信息
        cin>>ch;
        str+=ch;
        cin>>ch;
        str+=ch;
        --s;
        int x=stoi(str,nullptr,16);
        str="";
        string tmp;
        if ((x&3)==0) {
            x>>=2;
            if (x>=60) {
                for (int i=1;i<=x-59;++i) {
                    cin>>ch;
                    tmp+=ch;
                    cin>>ch;
                    tmp+=ch;
                    --s;
                    str=tmp+str;
                    tmp="";
                }
                int len=stoi(str,nullptr,16)+1;
                for (int i=1;i<=len*2;++i) {
                    cin>>ch;
                    if (i%2==0) {
                        --s;
                    }
                    txt+=ch;
                }
            } else {
                for (int i=1;i<=(x+1)*2;++i) {
                    cin>>ch;
                    if (i%2==0) {
                        --s;
                    }
                    txt+=ch;
                }
            }
        } else {
            int o,l;
            if ((x&3)==1) {
                l=((x&28)>>2)+4;
                o=(x&224)<<3;
                cin>>ch;
                str+=ch;
                cin>>ch;
                str+=ch;
                --s;
                o+=stoi(str,nullptr,16);
            } else if ((x&3)==2) {
                l=(x>>2)+1;
                for (int i=1;i<=2;++i) {
                    cin>>ch;
                    tmp+=ch;
                    cin>>ch;
                    tmp+=ch;
                    --s;
                    str=tmp+str;
                    tmp="";
                }
                o=stoi(str,nullptr,16);
            }
            //回溯
            int len=txt.length();
            int start=len-o*2;
            for (int i=0;i<l*2;++i) {
                txt+=txt[start+i%(len-start)];
            }
        }
        str="";
    }
    for (int i=0;i<txt.length();++i) {
        if (i%16==0 && i) {
            cout<<'\n';
        }
        cout<<txt[i];
    }
    return 0;
}