#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;

struct Trie {
	int tot = 1;
	int tr[N][30], ed[N];

	void insert(std::string str) {
		int len = str.size(), p = 1;
		for (int k = 0; k < len; k++) {
			int ch = str[k] - 'a';
			if (!tr[p][ch])
				tr[p][ch] = ++tot;
			p = tr[p][ch];
		}
		ed[p]++;
	}

	int search(std::string str) {
		int len = str.size(), p = 1;
		int ret = 0;
		for (int k = 0; k < len; k++) {
			int ch = str[k] - 'a';
			p = tr[p][ch];
			if (!p)
				return ret;
			ret += ed[p];
		}
		return ret;
	}
} trie;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::string str;
		std::cin >> str;
		trie.insert(str);
	}
	for (int i = 1; i <= m; i++) {
		std::string str;
		std::cin >> str;
		std::cout << trie.search(str) << "\n";
	}
	return 0;
}
