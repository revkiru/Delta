#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int M = 2e5 + 7;

int n, m, s;
int dis[N], vis[N];

struct edge {
	int to, val;
};
std::vector<edge> G[M << 1];

struct node {
	int id, w;

	friend bool operator < (const node &a, const node &b) {
		return a.w > b.w;
	}
};

void dij() {
	memset(dis, 0x7f, sizeof(dis));
	std::priority_queue<node> q;
	dis[s] = 0;
	q.push({s, 0});
	while (!q.empty()) {
		int u = q.top().id;
		q.pop();
		if (vis[u]) continue;
		vis[u] = 1;
		for (size_t i = 0; i < G[u].size(); i++) {
			int v = G[u][i].to, w = G[u][i].val;
			if (dis[v] > (i64) dis[u] + w) {
				dis[v] = dis[u] + w;
				q.push({v, dis[v]});
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> s;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
	}
	dij();
	for (int i = 1; i <= n; i++)
		std::cout << dis[i] << " ";
	std::cout << "\n";
	return 0;
}
