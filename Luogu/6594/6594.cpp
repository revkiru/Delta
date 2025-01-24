#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 807;
constexpr int inf = 1e9;

int n, m, k, base;
int l = inf, r = -inf;
int lo[N][N], h[N], f[N][N];
int dep[N], siz[N], fa[N][12];

std::vector<int> G[N << 1];

void dfs0(int u, int pa, int dee) {
	dep[u] = dee, fa[u][0] = pa;
	for (int i = 1; (1 << i) <= dee; i++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == pa) continue;
		dfs0(v, u, dee + 1);
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y])
		std::swap(x, y);
	for (int t = dep[x] - dep[y], c = 0; t; t >>= 1, c++) {
		if (t & 1)
			x = fa[x][c];
	}
	if (x == y)
		return x;
	for (int i = 11; ~i; i--) {
		if (fa[x][i] != fa[y][i]) {
			x = fa[x][i];
			y = fa[y][i];
		}
	}
	return fa[x][0];
}

void dfs1(int u, int pa) {
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == pa) continue;
		dfs1(v, u);
		siz[u] += siz[v];
	}
}

void dfs2(int u, int pa, int c) {
	lo[c][u] = 1;
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == pa || h[v] < h[c] || h[v] - h[c] > base)
			continue;
		dfs2(v, u, c);
	}
}

void dfs3(int u, int pa) {
	for (int i = 1; i <= n; i++) {
		if (lo[i][u]) f[i][u] = 0;
		else f[i][u] = inf;
	}
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == pa) continue;
		dfs3(v, u);
		int mn = inf;
		for (int j = 1; j <= n; j++)
			mn = std::min(mn, f[j][v]);
		mn += siz[v];
		for (int j = 1; j <= n; j++)
			if (f[j][u] < inf)
				f[j][u] += std::min(mn, f[j][v]);
	}
}

int check(int p) {
	base = p;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			lo[i][j] = 0;
		dfs2(i, 0, i);
	}
	dfs3(1, 0);
	int ans = inf;
	for (int i = 1; i <= n; i++)
		ans = std::min(ans, f[i][1]);
	return ans;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> h[i];
		l = std::min(l, h[i]);
		r = std::max(r, h[i]);
	}
	for (int i = 1, u, v; i < n; i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs0(1, 0, 0);
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		++siz[x], ++siz[y];
		siz[lca(x, y)] -= 2;
	}
	dfs1(1, 0);
	l = 0, r = r - l;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid) <= k)
			r = mid;
		else
			l = mid + 1;
	}
	if (check(l) <= k)
		std::cout << l << "\n";
	else
		std::cout << r << "\n";
	return 0;
}
