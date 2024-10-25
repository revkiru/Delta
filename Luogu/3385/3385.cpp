#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e3 + 7;
constexpr int inf = 1e9;

int n, m;
int dis[N], vis[N], cnt[N];

struct edge {
	int to, val;
};

std::vector<edge> G[N << 1];

void init() {
	for (int i = 1; i <= n; i++) { dis[i] = inf; vis[i] = 0; cnt[i] = 0; G[i].clear(); }
}

int spfa() {
	std::queue<int> q;
	q.push(1);
	dis[1] = 0, vis[1] = 1, cnt[1]++;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		vis[u] = 0;
		for (size_t i = 0; i < G[u].size(); i++) {
			int v = G[u][i].to, w = G[u][i].val;
			if (dis[v] > (i64) dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!vis[v]) {
					vis[v] = 1;
					q.push(v);
					cnt[v]++;
					if (cnt[v] > n)
						return 1;
				}
			}
		}
	}
	return 0;
}

void solve() {
	std::cin >> n >> m;
	init();
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
		if (w >= 0) {
			G[v].push_back({u, w});
		}
	}
	if (spfa())
		std::cout << "YES\n";
	else
		std::cout << "NO\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
