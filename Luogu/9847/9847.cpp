#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
i64 a[N], t[N], f[N], g[N];
i64 pre[N], suf[N];

std::vector<int> G[N << 1];

void init() {
	for (int i = 1; i <= n; i++)
		G[i].clear();
}

void dfs(int u, int pa) {
	f[u] = g[u] = 0;
	bool flg = 0;
	i64 mx = 0;
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == pa)
			continue;
		dfs(v, u);
		g[u] += f[v];
		flg = flg || t[v] == 3;
		mx = std::max(mx, a[v]);
	}
	f[u] = g[u] + mx;
	// std::cout << u << ": " << f[u] << " " << g[u] << "...\n";
	if (flg) {
		int s = 0;
		for (auto i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (v == pa)
				continue;
			s++;
			if (t[v] == 3)
				pre[s] = suf[s] = a[v];
			else
				pre[s] = suf[s] = 0;
		}
		pre[0] = suf[s + 1] = 0; 
		for (int i = 1; i <= s; i++) {
			pre[i] = std::max(pre[i], pre[i - 1]);
			// std::cout << pre[i] << " ";
		}
		for (int i = s; i >= 1; i--) {
			suf[i] = std::max(suf[i], suf[i + 1]);
			// std::cout << suf[i] << "!!!\n";
		}
		s = 0;
		for (auto i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (v == pa)
				continue;
			s++;
			f[u] = std::max(f[u], g[u] + std::max(pre[s - 1], suf[s + 1]) + a[v] + g[v] - f[v]);
		}
	}
}

void solve() {
	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= n; i++)
		std::cin >> t[i];
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0);
	std::cout << f[1] + a[1] << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		init();
		solve();
	}
	return 0;
}
