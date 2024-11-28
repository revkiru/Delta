#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n, ans;
int a[N];

struct Trie {
	int tr[N * 32][2], tot = 1;

	void insert(int val) {
		int p = 1;
		for (int k = 30; k >= 0; k--) {
			int ch = (val >> k) & 1;
			if (!tr[p][ch])
				tr[p][ch] = ++tot;
			p = tr[p][ch];
		}
	}

	int search(int val) {
		int p = 1, ret = 0;
		for (int k = 30; k >= 0; k--) {
			int ch = (val >> k) & 1;
			if (tr[p][ch ^ 1]) {
				p = tr[p][ch ^ 1];
				ret |= (1 << k);
			} else {
				p = tr[p][ch];
			}
		}
		return ret;
	}
} trie;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		trie.insert(a[i]);
		ans = std::max(ans, trie.search(a[i]));
	}
	std::cout << ans << "\n";
	return 0;
}
