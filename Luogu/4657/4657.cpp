#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int M = 107;

int n, m, rt;
int f[N];
i64 ans;
i64 dp[N][M][2], g[N];
i64 rmax[N][M], rval[N][M], rscm[N][M];
std::vector<int> G[N << 1];

void dfs(int x, int fa) {
	g[x] = 0;
	for (int i = 1; i <= m; i++)
		dp[x][i][0] = 0;
	for (auto i = 0; i < G[x].size(); i++) {
		int y = G[x][i];
		if (y == fa) continue;
		g[x] += f[y];
		dfs(y, x);
		for (int j = 1; j <= m; j++)
			dp[x][j][0] = std::max({dp[x][j][0], dp[y][j][1], dp[y][j][0]});
	}
	for (int i = m; i >= 1; i--)
		dp[x][i][1] = dp[x][i - 1][0] + g[x];
}

void sol(int x, int fa) {
	for (int i = 1; i <= m; i++)
		dp[x][i][0] = std::max({dp[x][i][0], dp[fa][i][0], dp[fa][i][1]});
	for (int i = 1; i <= m; i++)
		dp[x][i][1] = dp[x][i - 1][0] + g[x] + f[fa];
	ans = std::max({ans, dp[x][m][0], dp[x][m][1]});
	for (int i = 1; i <= m; i++)
		dp[x][i][0] = std::max(dp[fa][i][0], dp[fa][i][1]);
	for (auto i = 0; i < G[x].size(); i++) {
		int y = G[x][i];
		for (int k = 1; k <= m; k++) {
			i64 val = 0;
			if (y == fa)
				val = std::max(dp[fa][k][0], dp[fa][k][1]);
			else
				val = std::max(dp[y][k][0], dp[y][k][1]);
			if (val > rval[x][k]) {
				rscm[x][k] = rval[x][k];
				rval[x][k] = val;
				rmax[x][k] = y;
			} else
				rscm[x][k] = std::max(rscm[x][k], val);
		}
	}
	for (auto i = 0; i < G[x].size(); i++) {
		int y = G[x][i];
		if (y == fa) continue;
		for (int j = 1; j <= m; j++)
			dp[x][j][0] = (rmax[x][j] == y ? rscm[x][j] : rval[x][j]);
		for (int j = 1; j <= m; j++)
			dp[x][j][1] = dp[x][j - 1][0] + g[x] - f[y] + f[fa];
		sol(y, x);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> f[i];
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	if (n == 1 || !m) { std::cout << "0\n"; exit(0); }
	if (n == 2) { std::cout << std::max(f[1], f[2]) << "\n"; exit(0); }
	dfs(1, 0);
	sol(1, 0);
	std::cout << ans << "\n";
	return 0;
}
