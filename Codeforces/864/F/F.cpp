#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3007;

int n, m, q;
int low, top, stc[N];
bool vis[N], ins[N];
short s, dis[N][N], fa[13][N][N];
std::vector<int> G[N];

void minIt(int &x, int y) { if (dis[s][x] > dis[s][y]) x = y; }

void jdg(int u) {
	vis[u] = 1;
	for (auto v : G[u]) {
		if (!vis[v])
			jdg(v);
		else if (ins[v])
			minIt(low, v);
	}
}

void dfs(int u) {
	stc[++top] = u;
	ins[u] = 1;
	dis[s][u] = top;
	for (int k = 0; (1 << k) < top; k++)
		fa[k][s][u] = stc[1 + (1 << k)];
	vis[u] = 1;
	for (auto v : G[u]) {
		if (low && !vis[v]) { jdg(v); continue; }	// 更优先的环
		if (!vis[v]) {
			dfs(v);
			if (low == v)
				low = 0;
		}	// 离开 v 之后要在 low 中清除 v
		else if (ins[v]) minIt(low, v);
	}
	top--;
	ins[u] = 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> q;
	for (int i = 1, u, v; i <= m; i++) {
		std::cin >> u >> v;
		G[u].push_back(v);
	}
	for (int i = 1; i <= n; i++)
		std::sort(G[i].begin(), G[i].end());
	for (int i = 1; i <= n; i++) {
		memset(vis, 0, sizeof(vis));
		s = i, low = 0;
		dis[s][low] = n + 1;
		dfs(i);
	}
	while (q--) {
		int qs, qt, qk;
		std::cin >> qs >> qt >> qk;
		if (dis[qs][qt] < qk) { std::cout << "-1\n"; continue; }
		qk--;
		for (int i = 0; qk >> i; i++)
			if (qk >> i & 1)
				qs = fa[i][qs][qt];
		std::cout << qs << "\n";
	}
	return 0;
}
