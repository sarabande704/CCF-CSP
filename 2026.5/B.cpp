#include <bits/stdc++.h>
using namespace std;
unsigned long long n;
int k,m; 

unsigned long long cal(unsigned long long x) {
	double res=(double)x/100*k;
	unsigned long long num=(unsigned long long)res;
	double dd=res-num;
	if (dd!=0) {
		++num;
	}
	return num;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n>>k>>m;
	int l=0,r=1000000001;
	while (l+1<r) {
		unsigned long long tmp=n;
		int mid=(l+r)>>1;
		int flag=1;
		for (int i=1;i<=m;++i) {
			unsigned long long bad=cal(tmp);
			if (tmp<(bad+mid)){
				flag=0;
				break;
			}
			tmp-=(mid+bad);
		}
		if (flag) {
			l=mid;
		} else {
			r=mid;
		}
	}
	cout<<l<<'\n';
	return 0;
}