#include <bits/stdc++.h>
using namespace std;
const unsigned long long mul=47055833459;
const unsigned long long m12=1ULL<<52;
const unsigned long long m25=1ULL<<39;
const unsigned long long mod12=1ULL<<12;
const unsigned long long mod25=1ULL<<25;
int n;
unsigned long long p38[11];  //存放38的幂次
int p26[6];  //存放26的幂次
unordered_map<int,string> mp12,mp25;  //存散列值和字符串映射的容器
string s;

//把代号的数字表示转化为十进制数
unsigned long long calA() {
	unsigned long long res=0;
	for (int i=1;i<=58;++i) {
		res<<=1;
		res+=s[i]-'0';
	}
	return res;
}

//把典型代号的数字表示转化为十进制数
int calB(int l,int r) {
	int res=0;
	for (int i=l;i<=r;++i) {
		res<<=1;
		res+=s[i]-'0';
	}
	return res-mod25;
}

//把12位散列值转化成十进制数
int calC12() {
	int res=0;
	for (int i=59;i<=70;++i) {
		res<<=1;
		res+=s[i]-'0';
	}
	return res;
}

//把25位散列值转化成十进制数
int calC25(int l,int r) {
	int res=0;
	for (int i=l;i<=r;++i) {
		res<<=1;
		res+=s[i]-'0';
	}
	return res;
}

//计算简单消息中的地址
int calpos() {
	int pos=0;
	for (int i=57;i<=71;++i) {
		pos<<=1;
		pos+=s[i]-'0';
	}
	return pos;
}

//把代号的数字表示转化成相应的字符串
string calAS(unsigned long long x) {
	string res="";
	unsigned long long tmp;
	for (int i=10;i>=0;--i) {
		tmp=x/p38[i];
		if (!tmp) {
			res+=" ";
		} else if (tmp<=10) {
			res+='0'+tmp-1;
		} else if (tmp<=36) {
			res+='A'+tmp-11;
		} else {
			res+='_';
		}
		x%=p38[i];
	}
	int cnt=0;
	for (int j=10;j>=0;--j) {
		if (res[j]!=' ') {
			break;
		}
		++cnt;
	}
	res.erase(11-cnt);
	return res;
}

//把典型代号的短数字表示转化成相应的字符串
string calBS(int x) {
	string res="";
	int tmp;
	for (int i=5;i>=0;--i) {
		tmp=x/p26[i];
		if (i==5) {
			if (!tmp) {
				;
			} else if (tmp<=10) {
				res+='0'+tmp-1;
			} else {
				res+='A'+tmp-11;
			}
		} else if (i==4) {
			if (tmp<=9) {
				res+='0'+tmp;
			} else {
				res+='A'+tmp-10;
			}
		} else if (i==3) {
			res+='0'+tmp;
		} else {
			res+='A'+tmp;
		}
		x%=p26[i];
	}
	return res;
}

//计算得到典型代号的短数字表示对应的字符串对应的完整数字表示
unsigned long long calBA(string str) {
	unsigned long long res=0;
	int len=str.length();
	for (int i=0;i<len;++i) {
		char tmp=str[i];
		if (tmp==' ') {
			continue;
		} else if (tmp>='0' && tmp<='9') {
			res+=(tmp-'0'+1)*p38[10-i];
		} else if (tmp>='A' && tmp<='Z') {
			res+=(tmp-'A'+11)*p38[10-i];
		} else {
			res+=37*p38[10-i];
		}
	}
	return res;
}

int cal12(unsigned long long x) {
	__int128_t res=(__int128_t)x;
	res*=mul;
	res/=m12;
	return (int)(res%mod12);
}

int cal25(unsigned long long x) {
	__int128_t res=(__int128_t)x;
	res*=mul;
	res/=m25;
	return (int)(res%mod25);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n;
	//计算38的幂次
	p38[0]=1;
	for (int i=1;i<=10;++i) {
		p38[i]=p38[i-1]*38ULL;
	}
	//计算26的幂次
	p26[0]=1;
	for (int i=1;i<=3;++i) {
		p26[i]=p26[i-1]*26;
	}
	p26[4]=p26[3]*10;
	p26[5]=p26[4]*36;
	while (n--) {
		cin>>s;
		if (s[0]=='0') {
			int receive,send,receive12=-1,receive25=-1,send12=-1,send25=-1;
			string receive_s,send_s;
			if (s[1]=='1' || s[2]=='1' || s[3]=='1') {
				receive=calB(1,28);
				receive_s=calBS(receive);
				receive12=cal12(calBA(receive_s));
				receive25=cal25(calBA(receive_s));
			} else {
				receive=calC25(4,28);
				if (mp25[receive]=="") {
					receive_s="###";
				} else {
					receive_s="#"+mp25[receive];
				}
			}
			if (s[29]=='1' || s[30]=='1' || s[31]=='1') {
				send=calB(29,56);
				send_s=calBS(send);
				send12=cal12(calBA(send_s));
				send25=cal25(calBA(send_s));
			} else {
				send=calC25(32,56);
				if (mp25[send]=="") {
					send_s="###";
				} else {
					send_s="#"+mp25[send];
				}
			}
			int pos=calpos();
			//更新查找表
			if (receive12!=-1) {
				mp12[receive12]=receive_s;
			}
			if (send12!=-1) {
				mp12[send12]=send_s;
			}
			if (receive25!=-1) {
				mp25[receive25]=receive_s;
			}
			if (send25!=-1) {
				mp25[send25]=send_s;
			}
			cout<<receive_s<<" "<<send_s;
			if (!pos) {
				cout<<'\n';
			} else {
				cout<<" "<<pos<<'\n';
			}
		} else {
			int last=s[71]-'0';
			if (last) {
				unsigned long long receive;
				int send;
				receive=calA();
				send=calC12();
				string receive_s,send_s;
				receive_s=calAS(receive);
				if (mp12[send]!="") {
					send_s="#"+mp12[send];
				} else {
					send_s="###";
				}
				int receive12=cal12(receive);
				int receive25=cal25(receive);
				mp12[receive12]=receive_s;
				mp25[receive25]=receive_s;
				cout<<receive_s<<" "<<send_s<<'\n';
			} else {
				unsigned long long send;
				int receive;
				send=calA();
				receive=calC12();
				string receive_s,send_s;
				send_s=calAS(send);
				if (mp12[receive]!="") {
					receive_s="#"+mp12[receive];
				} else {
					receive_s="###";
				}
				int send12=cal12(send);
				int send25=cal25(send);
				mp12[send12]=send_s;
				mp25[send25]=send_s;
				cout<<receive_s<<" "<<send_s<<'\n';
			}
		}
	}
    return 0;
}