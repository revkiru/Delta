#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;
constexpr int inf = 0x3f3f3f3f;

int n, m, ans;
int _x, _y, __x, __y;
int ind[N], len[N], dis[5][N];
bool vis[N];

struct edge {
	int to, val;
};

std::vector<edge> G[N << 1], G2[N << 1];

void dij(int id, int st) {
	memset(vis, 0, sizeof(vis));
	memset(dis[id], inf, sizeof(dis[id]));
	dis[id][st] = 0;
	for (int i = 1; i <= n; i++) {
		int d = inf, u = -1;
		for (int j = 1; j <= n; j++) {
			if (!vis[j] && d > dis[id][j]) {
				d = dis[id][j];
				u = j;
			}
		}
		if (u == -1)
			break;
		vis[u] = 1;
		for (size_t i = 0; i < G[u].size(); i++) {
			int v = G[u][i].to, w = G[u][i].val;
			dis[id][v] = std::min(dis[id][v], dis[id][u] + w);
		}
	}
}

void topo() {
	std::queue<int> q;
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= n; i++)
		if (!ind[i])
			q.push(i);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (size_t i = 0; i < G2[u].size(); i++) {
			int v = G2[u][i].to, w = G2[u][i].val;
			ind[v]--;
			len[v] = std::max(len[v], len[u] + w);
			if (ind[v] == 0)
				q.push(v);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	std::cin >> _x >> _y >> __x >> __y;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}

	dij(1, _x);
	dij(2, _y);
	dij(3, __x);
	dij(4, __y);

	for (int i = 1; i <= n; i++) {
		for (size_t j = 0; j < G[i].size(); j++) {
			int v = G[i][j].to, w = G[i][j].val;
			if (dis[1][i] + w + dis[2][v] == dis[1][_y]) {
				if (dis[3][i] + w + dis[4][v] == dis[3][__y]) {
					G2[i].push_back({v, w});
					ind[v]++;
				}
			}
		}
	}
	topo();
	for (int i = 1; i <= n; i++)
		ans = std::max(ans, len[i]);

	memset(ind, 0, sizeof(ind));
	memset(len, 0, sizeof(len));
	for (int i = 0; i <= n; i++)
		G2[i].clear();
	for (int i = 1; i <= n; i++) {
		for (size_t j = 0; j < G[i].size(); j++) {
			int v = G[i][j].to, w = G[i][j].val;
			if (dis[1][i] + w + dis[2][v] == dis[1][_y]) {
				if (dis[4][i] + w + dis[3][v] == dis[3][__y]) {
					G2[i].push_back({v, w});
					ind[v]++;
				}
			}
		}
	}

	topo();
	for (int i = 1; i <= n; i++)
		ans = std::max(ans, len[i]);
	std::cout << ans << "\n";
	return 0;
}
