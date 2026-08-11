#include <bits/stdc++.h>
using namespace std;
int n, N, q, o, a;

struct line {
	bool tag = false;
	int mem = -1;
	int pre = -1;
	int next = -1;
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cin >> n >> N >> q;
	vector<vector<struct line>> cache(N, vector<struct line>(n));
	for (int i = 0; i < N; ++i) {
		if (n == 1) {
			cache[i][0].pre = -1;
			cache[i][0].next = -1;
		} else {
			for (int j = 0; j < n; ++j) {
				cache[i][j].pre = j - 1;
				cache[i][j].next = j + 1;
			}
			cache[i][0].pre = -1;
			cache[i][n - 1].next = -1;
		}
	}
	vector<int> empty(N, 0);
	unordered_map<int, int> mp;
	vector<int> head(N, 0), tail(N, n - 1);
	while (q--) {
		cin >> o >> a;
		int k = (a / n) % N;
		if (o == 0) {
			auto it = mp.find(a);
			if (it != mp.end()) {
				int l = mp[a];
				if (cache[k][l].pre == -1) {
					if (cache[k][l].next != -1) {
						head[k] = cache[k][l].next;
						cache[k][cache[k][l].next].pre = -1;
						cache[k][tail[k]].next = l;
						cache[k][l].pre = tail[k];
						cache[k][l].next = -1;
					}
				} else if (cache[k][l].next != -1) {
					cache[k][cache[k][l].next].pre = cache[k][l].pre;
					cache[k][cache[k][l].pre].next = cache[k][l].next;
					cache[k][l].pre = tail[k];
					cache[k][l].next = -1;
					cache[k][tail[k]].next = l;
				}
				tail[k] = l;
			} else {
				if (empty[k] < n) {
					mp.erase(a);
					mp[a] = empty[k];
					cout << 0 << ' ' << a << '\n';
					cache[k][empty[k]].tag = false;
					cache[k][empty[k]].mem = a;
					int l = empty[k];
					if (cache[k][l].pre == -1) {
						if (cache[k][l].next != -1) {
							head[k] = cache[k][l].next;
							cache[k][cache[k][l].next].pre = -1;
							cache[k][tail[k]].next = l;
							cache[k][l].pre = tail[k];
							cache[k][l].next = -1;
						}
					} else if (cache[k][l].next != -1) {
						cache[k][cache[k][l].next].pre = cache[k][l].pre;
						cache[k][cache[k][l].pre].next = cache[k][l].next;
						cache[k][l].pre = tail[k];
						cache[k][l].next = -1;
						cache[k][tail[k]].next = l;
					}
					tail[k] = l;
					++empty[k];
				} else {
					int l = head[k];
					mp.erase(a);
					mp[a] = l;
					if (cache[k][l].tag) {
						cout << 1 << ' ' << cache[k][l].mem << '\n';
					}
					mp.erase(cache[k][l].mem);
					cache[k][l].tag = false;
					cache[k][l].mem = a;
					cout << 0 << ' ' << a << '\n';
					if (cache[k][l].pre == -1) {
						if (cache[k][l].next != -1) {
							head[k] = cache[k][l].next;
							cache[k][cache[k][l].next].pre = -1;
							cache[k][tail[k]].next = l;
							cache[k][l].pre = tail[k];
							cache[k][l].next = -1;
						}
					} else if (cache[k][l].next != -1) {
						cache[k][cache[k][l].next].pre = cache[k][l].pre;
						cache[k][cache[k][l].pre].next = cache[k][l].next;
						cache[k][l].pre = tail[k];
						cache[k][l].next = -1;
						cache[k][tail[k]].next = l;
					}
					tail[k] = l;
				}
			}
		} else {
			auto it = mp.find(a);
			if (it != mp.end()) {
				int l = mp[a];
				cache[k][l].tag = true;
				if (cache[k][l].pre == -1) {
					if (cache[k][l].next != -1) {
						head[k] = cache[k][l].next;
						cache[k][cache[k][l].next].pre = -1;
						cache[k][tail[k]].next = l;
						cache[k][l].pre = tail[k];
						cache[k][l].next = -1;
					}
				} else if (cache[k][l].next != -1) {
					cache[k][cache[k][l].next].pre = cache[k][l].pre;
					cache[k][cache[k][l].pre].next = cache[k][l].next;
					cache[k][l].pre = tail[k];
					cache[k][l].next = -1;
					cache[k][tail[k]].next = l;
				}
				tail[k] = l;
			} else {
				if (empty[k] < n) {
					mp.erase(a);
					mp[a] = empty[k];
					cout << 0 << ' ' << a << '\n';
					cache[k][empty[k]].tag = true;
					cache[k][empty[k]].mem = a;
					int l = empty[k];
					if (cache[k][l].pre == -1) {
						if (cache[k][l].next != -1) {
							head[k] = cache[k][l].next;
							cache[k][cache[k][l].next].pre = -1;
							cache[k][tail[k]].next = l;
							cache[k][l].pre = tail[k];
							cache[k][l].next = -1;
						}
					} else if (cache[k][l].next != -1) {
						cache[k][cache[k][l].next].pre = cache[k][l].pre;
						cache[k][cache[k][l].pre].next = cache[k][l].next;
						cache[k][l].pre = tail[k];
						cache[k][l].next = -1;
						cache[k][tail[k]].next = l;
					}
					tail[k] = l;
					++empty[k];
				} else {
					int l = head[k];
					mp.erase(a);
					mp[a] = l;
					if (cache[k][l].tag) {
						cout << 1 << ' ' << cache[k][l].mem << '\n';
					}
					mp.erase(cache[k][l].mem);
					cache[k][l].tag = true;
					cache[k][l].mem = a;
					cout << 0 << ' ' << a << '\n';
					if (cache[k][l].pre == -1) {
						if (cache[k][l].next != -1) {
							head[k] = cache[k][l].next;
							cache[k][cache[k][l].next].pre = -1;
							cache[k][tail[k]].next = l;
							cache[k][l].pre = tail[k];
							cache[k][l].next = -1;
						}
					} else if (cache[k][l].next != -1) {
						cache[k][cache[k][l].next].pre = cache[k][l].pre;
						cache[k][cache[k][l].pre].next = cache[k][l].next;
						cache[k][l].pre = tail[k];
						cache[k][l].next = -1;
						cache[k][tail[k]].next = l;
					}
					tail[k] = l;
				}
			}
		}
	}
	return 0;
}