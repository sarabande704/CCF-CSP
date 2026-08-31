#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> res1,res2;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin>>n;
	double d;
	while (n--) {
		cin>>d;
		int num=(int)d;
		double dd=d-num;
		if (dd>0.5) {
			num+=1;
			res1.push_back(num);
			res2.push_back(num);
		} else if (dd==0.5) {
			res1.push_back(num+1);
			if (num%2) {
				res2.push_back(num+1);
			} else {
				res2.push_back(num);
			}
		} else {
			res1.push_back(num);
			res2.push_back(num);
		}
	}
	for (int it:res1) {
		cout<<it<<" ";
	}
	cout<<endl;
	for (int it:res2) {
		cout<<it<<" ";
	}
	return 0;
}
