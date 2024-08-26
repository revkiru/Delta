#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5007;
constexpr int P = 998244353;

int n;
int b[N], tg[N], tp[N], pr[N];
int fa[4];
i64 f[N][2], g[2];
std::vector<int> E[N];

void init() { fa[0] = 0; fa[1] = 1; fa[2] = 2; fa[3] = 3; }

int find(int x) { return (fa[x] ^ x) ? (fa[x] = find(fa[x])) : (x); }

int chk(int x, int y)  { return (find(x) == find(y)); }

int merge(int x, int y) {
	x = find(x), y = find(y);
	if (x == y) return 0;
	fa[x] = y;
	return 1;
}

void dpMerge(int u, int v) {
	g[0] = g[1] = 0;
	for (int x = 0; x <= 1; x++) {
		if (f[u][x]) {
			for (int y = 0; y <= 1; y++) {
				if (f[v][y]) {
					i64 vx = f[u][x], vy = f[v][y];
					int bi = tg[u] && tg[v];
					int ci = tg[u] && !tg[v];
					int di = !tg[u] && tg[v];
					for (int a = 0; a <= 1; a++) {
						for (int b = 0; b <= bi; b++) {
							for (int c = 0; c <= ci; c++) {
								for (int d = 0; d <= di; d++) {
									init();
									if (x) merge(0, 1);
									if (y) merge(2, 3);
									if (a && !merge(0, 2)) continue;
									if (b && !merge(1, 3)) continue;
									if (c && !merge(1, 2)) continue;
									if (d && !merge(0, 3)) continue;
									if (!chk(2, 0) && !chk(2, 1)) continue;
									if (tg[v] && !chk(3, 0) && !chk(3, 1)) continue;
									g[chk(0, 1)] += vx * vy;
								}
							}
						}
					}
				}
			}
		}
	}
	f[u][0] = g[0] % P;
	f[u][1] = g[1] % P;
}

void calc(int u) {
	f[u][0] = 1;
	f[u][1] = 0;
	for (auto v : E[u]) {
		if (v ^ pr[u])
			dpMerge(u, v);
	}
}

void dfs(int u) {
	for (auto v : E[u]) {
		if (v ^ pr[u]) { pr[v] = u; dfs(v); }
	}
	calc(u);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("tree.in", "r", stdin);
	// freopen("tree.out", "w", stdout);

	std::cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		E[u].push_back(v);
		E[v].push_back(u);
	}

	for (int i = 1; i < n; i++)
		std::cin >> b[i];
	dfs(1);

	for (int i = 1; i < n; i++) {
		tg[b[i]] = 1;
		for (int p = b[i]; p; p = pr[p])
			calc(p);
		i64 ret = f[1][tg[1]];
		std::cout << ret << "\n";
	}
	return 0;
}
