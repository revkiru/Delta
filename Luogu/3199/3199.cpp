#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr double eps = 1e-9;

int n, m;
double dis[N];
bool vis[N];

struct edge {
	int to;
	double val;
};

std::vector<edge> G[N << 1];

bool spfa(int u, double mid) {
	vis[u] = 1;
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i].to;
		double w = G[u][i].val - mid;
		if (dis[u] + w < dis[v]) {
			dis[v] = dis[u] + w;
			if (vis[v] || spfa(v, mid))
				return 1;
		}
	}
	vis[u] = 0;
	return 0;
}

bool check(double mid) {
	for (int i = 1; i <= n; i++) {
		dis[i] = 0;
		vis[i] = 0;
	}
	for (int i = 1; i <= n; i++)
		if (spfa(i, mid))
			return 1;
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		double w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
	}

	double l = -1e7, r = 1e7;
	while (r - l >= eps) {
		double mid = (l + r) / 2;
		// std::cout << mid << "\n";
		if (check(mid))
			r = mid;
		else
			l = mid;
	}
	std::cout << std::fixed << std::setprecision(8) << l << "\n";
	return 0;
}
