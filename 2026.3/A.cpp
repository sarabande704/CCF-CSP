#include <iostream>
using namespace std;

bool is_balance(int x) {
	int cnt0=0,cnt1=0;
	while (x) {
		if (x-(x/2)*2) {
			++cnt1;
		} else {
			++cnt0;
		}
		x/=2;
	}
	return cnt1==cnt0;
}

int main() {
	int n,a,cnt=0;
	cin>>n;
	for (int i=1;i<=n;++i) {
		cin>>a;
		if (is_balance(a)) {
			++cnt;
		}
	}
	cout<<cnt<<endl;
	return 0;
}