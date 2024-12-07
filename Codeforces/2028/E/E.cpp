#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;
constexpr int P = 998244353;

int inv[N];

void init() {
	inv[1] = 1;
	for (int i = 2; i <= (int) 2e5; i++) {
		inv[i] = (P - P / i) * inv[P % i] % P;
	}
}

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> dp(n + 1);
	for (int i = 1; i <= n; i++) {
		dp[i] = (i == 1 ? 0 : n + 1);
	}

	std::vector<int> G[n * 2];
	for (int i = 1, x, y; i < n; i++) {
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}

	std::function<void(int, int)> dfs1 = [&](int u, int fa) {
		bool flg = 0;
		for (auto v : G[u]) {
			if (v == fa)
				continue;
			flg = 1;
			dfs1(v, u);
			dp[u] = std::min(dp[u], dp[v] + 1);
		}
		if (!flg)
			dp[u] = 0;
	};
	dfs1(1, 1);

	std::vector<int> ans(n + 1);
	ans[1] = 1;
	std::function<void(int, int)> dfs2 = [&](int u, int fa) {
		for (auto v : G[u]) {
			if (v == fa)
				continue;
			ans[v] = ans[u] * dp[v] % P * inv[dp[v] + 1] % P;
			dfs2(v, u);
		}
	};
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
		std::cout << ans[i] << (i == n ? "\n" : " ");
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
