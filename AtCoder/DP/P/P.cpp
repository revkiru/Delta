#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int P = 1e9 + 7;

int n;
i64 dp[N][2];
std::vector<int> G[N << 1];

void dfs(int u, int fa) {
	dp[u][0] = dp[u][1] = 1;
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == fa) continue;
		dfs(v, u);
		dp[u][0] = (dp[u][0] * (dp[v][0] + dp[v][1])) % P;
		dp[u][1] = (dp[u][1] * dp[v][0]) % P;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x, y; i < n; i++) {
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	dfs(1, 0);
	std::cout << ((dp[1][0] + dp[1][1]) % P) << "\n";
	return 0;
}
