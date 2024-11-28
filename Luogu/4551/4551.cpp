#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, ans;
int d[N];

struct edge {
	int to, val;
};

std::vector<edge> G[N << 1];

struct Trie {
	int tr[N * 32][2], tot = 1;

	void insert(int val) {
		int p = 1;
		for (int k = 31; k >= 0; k--) {
			int ch = (val >> k) & 1;
			if (!tr[p][ch])
				tr[p][ch] = ++tot;
			p = tr[p][ch];
		}
	}

	int search(int val) {
		int p = 1, ret = 0;
		for (int k = 31; k >= 0; k--) {
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

void dfs(int x, int fa) {
	for (size_t i = 0; i < G[x].size(); i++) {
		int y = G[x][i].to, z = G[x][i].val;
		if (y == fa)
			continue;
		d[y] = d[x] ^ z;
		dfs(y, x);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i < n; i++) {
		int x, y, z;
		std::cin >> x >> y >> z;
		G[x].push_back({y, z});
		G[y].push_back({x, z});
	}

	d[0] = 1;
	dfs(1, 0);
	for (int i = 0; i < n; i++)
		trie.insert(d[i]);

	for (int i = 1; i <= n; i++)
		ans = std::max(ans, trie.search(d[i]));
	std::cout << ans << "\n";
	return 0;
}
