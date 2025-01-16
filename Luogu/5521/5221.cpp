#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int w[N], f[N], g[N];

std::vector<int> G[N];

int cmp(int x, int y) {
	return w[x] + f[y] < w[y] + f[x];
}

void dfs(int u) {
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		dfs(v);
		g[u] = std::max(g[u], g[v]);
	}
	std::sort(G[u].begin(), G[u].end(), cmp);
	int res = 0;
	for (size_t i = 0; i < G[u].size(); i++) {
		f[u] = std::max(f[u], res + g[G[u][i]]);
		res += w[G[u][i]];
	}
	f[u] = std::max(f[u], res + w[u]);
	g[u] = std::max(g[u], f[u]);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 2, x; i <= n; i++) {
		std::cin >> x;
		G[x].push_back(i);
	}
	for (int i = 1; i <= n; i++)
		std::cin >> w[i];
	dfs(1);
	for (int i = 1; i <= n; i++)
		std::cout << f[i] << " ";
	std::cout << "\n";
	return 0;
}
