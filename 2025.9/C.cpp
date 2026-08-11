#include <bits/stdc++.h>
using namespace std;
int n, s, d, front = 0;
pair<string, string> static_table[66], dynamic_table[122];

map<char, string> mp = {{'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'a', "1010"}, {'b', "1011"}, {'c', "1100"}, {'d', "1101"}, {'e', "1110"}, {'f', "1111"}};

struct Node {
	char data;
	shared_ptr<Node> left;
	shared_ptr<Node> right;

	Node(char d) : data(d), left(nullptr), right(nullptr) {}
	Node() : data('\0'), left(nullptr), right(nullptr) {}
};
shared_ptr<Node> root;

shared_ptr<Node> rebuildHuffmanTree(const string &s, int &index) {
	if (index >= s.length())
		return nullptr;

	if (s[index] == '1') {
		index++; // Ìø¹ý'1'
		char ch = s[index++]; // ¶ÁÈ¡×Ö·û
		return make_shared<Node>(ch);
	} else if (s[index] == '0') {
		index++; // Ìø¹ý'0'
		auto node = make_shared<Node>();
		node->left = rebuildHuffmanTree(s, index);
		node->right = rebuildHuffmanTree(s, index);
		return node;
	}
	return nullptr;
}

void init() {
	cin >> s >> d;
	string str1, str2;
	for (int i = 1; i <= s; ++i) {
		cin >> str1 >> str2;
		static_table[i] = {str1, str2};
	}
	cin >> str1;
	int index = 0;
	root = rebuildHuffmanTree(str1, index);
	cin >> n;
}

string func(string &s) {
	int l = s.length();
	char ch = s[0];
	if (ch == 'H') {
		char ch1 = s[1];
		if (ch1 == 'H') {
			return s.substr(1);
		} else {
			string tmp1 = "", tmp2, res = "";
			for (int i = 1; i < l - 2; ++i) {
				tmp1 += mp[s[i]];
			}
			int k = s[l - 1] - '0';
			tmp2 = tmp1.substr(0, (l - 3) * 4 - k);
			auto it = root;
			for (char c : tmp2) {
				if (c == '0') {
					it = it->left;
				} else {
					it = it->right;
				}
				if (it->data != '\0') {
					res += it->data;
					it = root;
				}
			}
			return res;
		}
	} else {
		return s;
	}
}

void solve() {
	int op, num;
	string k, v;
	for (int i = 1; i <= n; ++i) {
		cin >> op;
		if (op == 1) {
			cin >> num;
			if (num <= s) {
				cout << static_table[num].first << ": " << static_table[num].second << "\n";
			} else {
				int index = (front + num - s - 1) % d;
				cout << dynamic_table[index].first << ": " << dynamic_table[index].second << "\n";
			}
		} else {
			cin >> num;
			if (num == 0) {
				cin >> k >> v;
				k = func(k);
				v = func(v);
				cout << k << ": " << v << '\n';
			} else {
				cin >> v;
				v = func(v);
				if (num <= s) {
					cout << static_table[num].first << ": " << v << "\n";
				} else {
					int index = (front + num - s - 1) % d;
					cout << dynamic_table[index].first << ": " << v << "\n";
				}
			}
		}
		if (op == 2) {
			--front;
			front = (front + d) % d;
			if (num == 0) {
				dynamic_table[front] = {k, v};
			} else {
				if (num <= s) {
					dynamic_table[front] = {static_table[num].first, v};
				} else {
					int index = (front + num - s) % d;
					dynamic_table[front] = {dynamic_table[index].first, v};
				}
			}
		}
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	solve();
	return 0;
}