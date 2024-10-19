#include <bits/stdc++.h>

constexpr int N = 3e5 + 5;
constexpr int Log = 20;
constexpr int inf = 1e9;

int n, m;
int ans[N], s[N], t[N], w[N], dep[N], fa[N][Log];
int up[N << 2], down[N << 1];

std::vector<int> g[N];
std::vector<std::pair<int, int>> v[N];

void dfs0(int u) {
	for (int i = 1; i < Log; i++)
		fa[u][i] = fa[fa[u][i - 1]][i - 1];
	
	for (size_t i = 0; i < g[u].size(); i++) {
		int v;
		if ((v = g[u][i]) == fa[u][0]) continue;
		fa[v][0] = u;
		dep[v] = dep[u] + 1;
		dfs0(v);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v]) std::swap(u, v);
	for (int i = Log - 1; ~i; i--)
		if (dep[fa[u][i]] >= dep[v])
			u = fa[u][i];
	if (u == v) return u;
	for (int i = Log - 1; ~i; i--)
		if (fa[u][i] != fa[v][i])
			u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

void addr(int s, int t, int w = 0) {
	if (dep[s] < dep[t]) { w += inf; std::swap(s, t); };
	v[s].push_back({w, 1});
	v[t].push_back({w, -1});
}

void dfs(int u) {
	ans[u] -= up[dep[u] + w[u]] + down[(N << 1) + dep[u] - w[u]];
	for (size_t i = 0; i < g[u].size(); i++) {
		if (g[u][i] == fa[u][0]) continue;
		dfs(g[u][i]);
	}
	for (size_t i = 0; i < v[u].size(); i++) {
		if (v[u][i].first > inf / 2) down[(N << 1) + v[u][i].first - inf] += v[u][i].second;
		else up[v[u][i].first] += v[u][i].second;
	}
	ans[u] += up[dep[u] + w[u]] + down[(N << 1) + dep[u] - w[u]];
}

int main() {
	scanf("%d %d", &n, &m);
	dep[0] = -1;
	for (int i = 1, u, v; i < n; i++) {
		scanf("%d %d", &u, &v);
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs0(1);
	for (int i = 1; i <= n; i++)
		scanf("%d", &w[i]);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &s[i], &t[i]);
		int u = lca(s[i], t[i]);
		if (u == s[i]) addr(fa[s[i]][0], t[i], dep[s[i]]);
		else if (u == t[i]) addr(s[i], fa[t[i]][0], dep[s[i]]);
		else {
			addr(s[i], fa[u][0], dep[s[i]]);
			addr(u, t[i], dep[u] - (dep[s[i]] - dep[u]));
		}
	}
	dfs(1);
	for (int i = 1; i <= n; i++)
		printf("%d ", ans[i]);
	printf("\n");
	return 0;
}
