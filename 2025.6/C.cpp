#include <bits/stdc++.h>
using namespace std;
int n;
string str;
uint64_t a = 38ULL * 38 * 38 * 38 * 38 * 38 * 38 * 38 * 38 * 38;
int m = 6327360;
map<uint32_t, vector<vector<string>>> mp;

uint64_t int_pow(int base, int exp) {
	uint64_t res = 1;
	for (int i = 0; i < exp; ++i)
		res *= base;
	return res;
}

void to_25(uint64_t num, string &s, string op, string p) {
	__uint128_t num1 = num * 47055833459ULL;
	num1 /= (1ULL << 39);
	num1 %= (1 << 25);
	mp[(uint32_t)num].push_back({s, op, p});
}

void to_12(uint64_t num, string &s, string op, string p) {
	__uint128_t num1 = num * 47055833459ULL;
	num1 /= (1ULL << 30);
	num1 /= (1ULL << 22);
	num1 %= (1 << 12);
	mp[(uint32_t)num].push_back({s, op, p});
}

void solve(int k, string &s) {
	char ch = s[0];
	if (ch == '0') {
		string s1 = "", s2 = "";
		uint64_t num = 0;
		for (int i = 1; i <= 28; ++i) {
			if (s[i] == '1') {
				num += (1ULL << (28 - i));
			}
		}
		uint64_t num1 = num;
		if (num >= (1ULL << 25)) {
			num -= int_pow(2, 25);
			num1 = num;
			for (int i = 1; i <= 6; ++i) {
				int ans;
				if (i == 1) {
					ans = num / m;
					num %= m;
					if (ans >= 1 && ans <= 10) {
						s1 += (char)('0' + ans - 1);
					} else if (ans >= 11 && ans <= 36) {
						s1 += (char)('A' + ans - 11);
					}
				} else if (i == 2) {
					ans = num / (m / 36);
					num %= (m / 36);
					if (ans >= 0 && ans <= 9) {
						s1 += (char)('0' + ans);
					} else if (ans >= 10 && ans <= 35) {
						s1 += (char)('A' + ans - 10);
					}
				} else {
					ans = num / int_pow(26, 6 - i);
					num %= int_pow(26, 6 - i);
					if (i == 3) {
						if (ans >= 0 && ans <= 9) {
							s1 += (char)('0' + ans);
						}
					} else {
						if (ans >= 0 && ans <= 25) {
							s1 += (char)('A' + ans);
						}
					}
				}
			}
		} else {
			vector<vector<string>> v = mp[(uint32_t)num1];
			if (v.size() == 0) {
				s1 = "###";
			} else {
				auto it1 = v[v.size() - 1];
				if (v.size() > 1 && v[v.size() - 2][2] == it1[2] && v[v.size() - 2][1] < it1[1]) {
					it1 = v[v.size() - 2];
				}
				s1 = "#" + it1[0];
			}
		}
		uint64_t num2 = 0;
		for (int i = 29; i <= 56; ++i) {
			if (s[i] == '1') {
				num2 += (1ULL << (56 - i));
			}
		}
		uint64_t num3 = num2;
		if (num2 >= (1ULL << 25)) {
			num2 -= int_pow(2, 25);
			num3 = num2;
			for (int i = 1; i <= 6; ++i) {
				int ans;
				if (i == 1) {
					ans = num2 / m;
					num2 %= m;
					if (ans >= 1 && ans <= 10) {
						s2 += (char)('0' + ans - 1);
					} else if (ans >= 11 && ans <= 36) {
						s2 += (char)('A' + ans - 11);
					}
				} else if (i == 2) {
					ans = num2 / (m / 36);
					num2 %= (m / 36);
					if (ans >= 0 && ans <= 9) {
						s2 += (char)('0' + ans);
					} else if (ans >= 10 && ans <= 35) {
						s2 += (char)('A' + ans - 10);
					}
				} else {
					ans = num2 / int_pow(26, 6 - i);
					num2 %= int_pow(26, 6 - i);
					if (i == 3) {
						if (ans >= 0 && ans <= 9) {
							s2 += (char)('0' + ans);
						}
					} else {
						if (ans >= 0 && ans <= 25) {
							s2 += (char)('A' + ans);
						}
					}
				}
			}
		} else {
			vector<vector<string>> v = mp[(uint32_t)num3];
			if (v.size() == 0) {
				s2 = "###";
			} else {
				auto it1 = v[v.size() - 1];
				if (v.size() > 1 && v[v.size() - 2][2] == it1[2] && v[v.size() - 2][1] < it1[1]) {
					it1 = v[v.size() - 2];
				}
				s2 = "#" + it1[0];
			}
		}
		to_25(num1, s1, "1", to_string(k));
		to_12(num1, s1, "1", to_string(k));
		to_25(num3, s2, "0", to_string(k));
		to_12(num3, s2, "0", to_string(k));
		int address = 0;
		for (int i = 57; i <= 71; ++i) {
			if (s[i] == '1') {
				address += int_pow(2, 71 - i);
			}
		}
		cout << s1 << " " << s2;
		if (address) {
			cout << " " << address << endl;
		}
	} else {
		string s1 = "", s2 = "";
		uint64_t num = 0;
		for (int i = 1; i <= 58; ++i) {
			if (s[i] == '1') {
				num += (1ULL << (58 - i));
			}
		}
		uint64_t num1 = num;
		for (int i = 0; i <= 10; ++i) {
			int ans;
			if (i <= 5) {
				ans = num / (a / int_pow(38, i));
				num %= (a / int_pow(38, i));
			} else {
				ans = num / int_pow(38, 10 - i);
				num %= int_pow(38, 10 - i);
			}
			if (ans == 0) {
				break;
			} else if (ans >= 1 && ans <= 10) {
				s1 += (char)('0' + ans - 1);
			} else if (ans >= 11 && ans <= 36) {
				s1 += (char)('A' + ans - 11);
			} else {
				s1 += '_';
			}
		}
		uint32_t num2 = 0;
		for (int i = 59; i <= 70; ++i) {
			if (s[i] == '1') {
				num2 += int_pow(2, 70 - i);
			}
		}
		vector<vector<string>> v = mp[(uint32_t)num2];
		if (v.size() == 0) {
			s2 = "###";
		} else {
			auto it1 = v[v.size() - 1];
			if (v.size() > 1 && v[v.size() - 2][2] == it1[2] && v[v.size() - 2][1] < it1[1]) {
				it1 = v[v.size() - 2];
			}
			s2 = "#" + it1[0];
		}
		to_25(num1, s1, s[71] == '0' ? "0" : "1", to_string(k));
		to_12(num1, s1, s[71] == '0' ? "0" : "1", to_string(k));
		if (s[71] == '0') {
			cout << s2 << " " << s1 << endl;
		} else {
			cout << s1 << " " << s2 << endl;
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> str;
		solve(i, str);
	}
	return 0;
}
