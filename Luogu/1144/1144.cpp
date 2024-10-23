#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int M = 2e6 + 7;
constexpr int P = 100003;

int n, m, tot;
int dis[N], ans[N];
bool vis[N];
std::vector<int> G[M];

void dij() {
	std::priority_queue<std::pair<int, int>> q;
	memset(dis, 0x7f, sizeof(dis));
	dis[1] = 0, ans[1] = 1;
	q.push({0, 1});

	while (!q.empty()) {
		int u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (size_t i = 0; i < G[u].size(); i++) {
			int v = G[u][i];
			if (dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				ans[v] = ans[u];
				q.push({-dis[v], v});
			} else if (dis[v] == dis[u] + 1) {
				ans[v] += ans[u];
				ans[v] %= P;
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dij();
	for (int i = 1; i <= n; i++)
		std::cout << ans[i] << "\n";
	return 0;
}
