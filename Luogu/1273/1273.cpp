#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3007;
constexpr int inf = 1e9;

int n, m, ncnt;
int dfn[N], siz[N], otd[N], val[N];
int _v[N], _w[N], f[N][N];
std::vector<int> G[N << 1];

void chkmax(int &x, int y) { x = std::max(x, y); }

int dfs(int u) {
	siz[u] = 1;
	dfn[u] = ++ncnt;
	_v[ncnt]= val[u], _w[ncnt] = u + m - 1 >= n;
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		siz[u] += dfs(v);
	}
	otd[dfn[u]] = ncnt + 1;
	return siz[u];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, t, t1, t2; i <= n - m; i++) {
		std::cin >> t;
		for (int j = 1; j <= t; j++) {
			std::cin >> t1 >> t2;
			G[i].push_back(t1);
			val[t1] -= t2;
		}
	}
	for (int i = n - m + 1, t; i <= n; i++) {
		std::cin >> t;
		val[i] += t;
	}
	dfs(1);
	for (int i = 0; i <= n + 1; i++) {
		for (int j = 0; j <= n; j++)
			f[i][j] = -inf;
	}
	f[1][0] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = n; ~j; j--) {
			if (f[i][j] > -inf) {
				chkmax(f[otd[i]][j], f[i][j]);
				chkmax(f[i + 1][j + _w[i]], f[i][j] + _v[i]);
			}
		}
	}
	for (int i = n; ~i; i--) {
		if (f[n + 1][i] >= 0) {
			std::cout << i << "\n";
			break;
		}
	}
	return 0;
}
