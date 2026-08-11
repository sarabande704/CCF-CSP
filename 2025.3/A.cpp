#include <bits/stdc++.h>
using namespace std;

int main() {
	int b, c, l, r;
	cin >> b >> c >> l >> r;
	long long res = 0;
	for (int i = l; i <= r; ++i) {
		if (i % 2 == 0) {
			res += (i *i + b *i + c);
		}
	}
	res *= 2;
	cout << res << endl;
	return 0;
}