#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2007;

int n, k, t0t, cl;
bool abl[N];
std::vector<int> G[N << 1];

void dfs(int u, int len, int lst = -1) {
	abl[u] = 1;
	++cl;
	for (auto v : G[u]) {
		if (v != lst && !abl[v]) {
			if (len == 0) continue;
			dfs(v, len - 1, u);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	int ans = 1;
	if (k & 1) {
		for (int i = 1; i <= n; i++) {
			for (auto v : G[i]) {
				for (int j = 1; j <= n; j++)
					abl[j] = 0;
				cl = 0;
				dfs(i, k / 2, v);
				dfs(v, k / 2, i);
				ans = std::max(ans, cl);
			}
		}
	} else {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				abl[j] = 0;
			cl = 0;
			dfs(i, k / 2);
			ans = std::max(ans, cl);
		}
	}
	std::cout << n - ans << "\n";
	return 0;
}
