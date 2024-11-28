#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;
int otd[N], deg[N];
double dis[N];

struct edge {
	int to, val;
};

std::queue<int> q;
std::vector<edge> G[N << 1];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, z;
		std::cin >> x >> y >> z;
		G[y].push_back({x, z});
		deg[x]++;
		otd[x]++;
	}

	q.push(n);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (size_t i = 0; i < G[u].size(); i++) {
			int v = G[u][i].to, w = G[u][i].val;
			dis[v] += (dis[u] + w) / deg[v];
			otd[v]--;
			if (!otd[v])
				q.push(v);
		}
	}
	std::cout << std::fixed << std::setprecision(2)
		<< dis[1] << "\n";
	return 0;
}
