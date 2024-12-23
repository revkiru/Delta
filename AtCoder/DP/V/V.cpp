#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, m;
int f[N], g[N];

std::vector<int> G[N], pre[N], suf[N];

void dfs1(int u, int fa) {
	f[u] = 1;
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == fa) continue;
		dfs1(v, u);
		f[u] = f[u] * (f[v] + 1) % m;
		pre[u].push_back(f[v] + 1);
		suf[u].push_back(f[v] + 1);
	}

	for (int i = 0; i < pre[u].size(); i++)
		pre[u][i] = pre[u][i] * pre[u][i - 1] % m;
	for (int i = suf[u].size() - 2; i >= 0; i--)
		suf[u][i] = suf[u][i] * suf[u][i + 1] % m;
}

void dfs2(int u, int fa) {
	int cnt = 0, x = pre[u].size();
	for (int i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == fa) continue;
		cnt++;
		if (x == 1) g[v] = g[u] + 1;
		else if (cnt == 1) g[v] = g[u] * suf[u][cnt] % m + 1;
		else if (cnt == x) g[v] = g[u] * pre[u][cnt - 2] % m + 1;
		else g[v] = g[u] * (pre[u][cnt - 2] * suf[u][cnt] % m) % m + 1;
		dfs2(v, u);
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, x, y; i < n; i++) {
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}

	dfs1(1, 0);
	g[1] = 1;
	dfs2(1, 0);

	for (int i = 1; i <= n; i++)
		std::cout << (f[i] * g[i] % m) << "\n";
	return 0;
}
