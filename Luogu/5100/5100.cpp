#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;
constexpr int M = 507;

int h, w, a, b, c;
int n, s, t;
int dis[M][M], f[N], vis[N];

std::vector<std::pair<int, int>> G[N << 1];
std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;

int loc(int i, int j) { return (i - 1) * w + j; }

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> h >> w;
	std::cin >> a >> b >> c;
	std::cin >> n;
	h++, w++;
	memset(dis, 1, sizeof(dis));
	memset(f, 1, sizeof(f));

	for (int i = 1; i <= n; i++) {
		std::cin >> s >> t;
		s++, t++;
		dis[s][t] = 0;
		if (i == 1) {
			f[loc(s, t)] = 0;
			q.push({0, loc(s, t)});
		}
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			dis[i + 1][j] = std::min(dis[i][j] + 1, dis[i + 1][j]);
			dis[i][j + 1] = std::min(dis[i][j] + 1, dis[i][j + 1]);
		}
	}
	for (int i = h; i >= 1; i--) {
		for (int j = w; j >= 1; j--) {
			dis[i - 1][j] = std::min(dis[i][j] + 1, dis[i - 1][j]);
			dis[i][j - 1] = std::min(dis[i][j] + 1, dis[i][j - 1]);
		}
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j <= w; j++) {
			G[loc(i, j) + h * w].push_back({loc(i, j), dis[i][j] * c});
			G[loc(i, j) + 2 * h * w].push_back({loc(i, j), dis[i][j] * c});
			G[loc(i, j)].push_back({loc(i, j) + h * w, b});
			G[loc(i, j)].push_back({loc(i, j) + 2 * h * w, b});
		}
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < w; j++) {
			G[loc(i, j)].push_back({loc(i, j + 1), c});
			G[loc(i, j + 1)].push_back({loc(i, j), c});
			G[loc(i, j) + h * w].push_back({loc(i, j + 1) + h * w, a});
			G[loc(i, j + 1) + h * w].push_back({loc(i, j) + h * w, a});
		}
	}
	for (int i = 1; i < h; i++) {
		for (int j = 1; j <= w; j++) {
			G[loc(i, j)].push_back({loc(i + 1, j), c});
			G[loc(i + 1, j)].push_back({loc(i, j), c});
			G[loc(i, j) + 2 * h * w].push_back({loc(i + 1, j) + 2 * h * w, a});
			G[loc(i + 1, j) + 2 * h * w].push_back({loc(i, j) + 2 * h * w, a});
		}
	}
	while (!q.empty()) {
		int u = q.top().second;
		q.pop();
		if (vis[u])
			continue;
		vis[u] = 1;
		for (auto v : G[u]) {
			if (f[v.first] > f[u] + v.second) {
				f[v.first] = f[u] + v.second;
				q.push({f[v.first], v.first});
			}
		}
	}
	std::cout << f[loc(s, t)] << "\n";
	return 0;
}
