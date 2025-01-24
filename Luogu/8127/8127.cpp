#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int inf = 1e9;

int n;
int v[N], f[N][4];
std::vector<int> G[N << 1];

void dfs(int u, int fa) {
	if (!v[u]) f[u][2] = f[u][3] = inf;
	else f[u][0] = f[u][1] = inf;
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v != fa) {
			dfs(v, u);
			int ch0 = f[u][0],
				ch1 = f[u][1],
				ch2 = f[u][2],
				ch3 = f[u][3];
			f[u][0] = std::min({inf, ch0 + f[v][0], ch2 + f[v][3] + 1});
			f[u][1] = std::min({inf, ch1 + f[v][2], ch3 + f[v][1] + 1});
			f[u][2] = std::min({inf, ch2 + f[v][0], ch0 + f[v][3] + 1});
			f[u][3] = std::min({inf, ch3 + f[v][2], ch1 + f[v][1] + 1});
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; i++)
		std::cin >> v[i];
	dfs(1, 0);
	int ans = std::min(f[1][0], f[1][3] + 1);
	ans >= inf ? std::cout << "impossible\n" : std::cout << ans << "\n";
	return 0;
}
