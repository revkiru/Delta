#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 207;
constexpr int P = 1e9 + 7;

int n, w, m;
int ind[N], siz[N];
i64 f[N][N][2];

struct edge {
	int to, val;
};
std::vector<edge> G[N << 1];

void dfs(int u) {
	siz[u] = 1;
	f[u][0][0] = f[u][1][1] = 1;
	for (auto i = 0; i < G[u].size(); i++) {
		int v = G[u][i].to, t = G[u][i].val;
		dfs(v);
		siz[u] += siz[v];
		for (auto j = siz[u]; j >= 0; j--) {
			int d1 = 0, d0 = 0;
			for (auto k = std::min(j, siz[v]); k >= 0; k--) {
				if (t) {
					d1 = (d1 + f[v][k][0] * f[u][j - k][1]) % P;
					d0 = (d0 + f[u][j - k][0] * f[v][k][1] + f[u][j - k][0] * f[v][k][0]) % P;
				} else {
					d1 = (d1 + f[u][j - k][1] * f[v][k][1]) % P;
					d0 = (d0 + f[u][j - k][0] * f[v][k][0] + f[u][j - k][0] * f[v][k][1]) % P;
				}
			}
			f[u][j][0] = d0;
			f[u][j][1] = d1;
			// std::cout << d0 << " " << d1 << "!!!\n";
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> w >> m;
	for (int i = 1, x, y; i <= m; i++) {
		std::string c;
		std::cin >> c >> x >> y;
		if (c[0] == 'A')
			G[x].push_back({y, 1});
		else
			G[x].push_back({y, 0});
		ind[y]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!ind[i])
			G[0].push_back({i, 1});
	}
	dfs(0);
	std::cout << f[0][w][0] << "\n";
	return 0;
}
