#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n;
i64 l, r, h, ans;
i64 w[20], dis[N];
bool vis[N];

struct edge {
	i64 to, val;
};
std::vector<edge> G[N << 1];

void spfa() {
	memset(dis, 0x3f, sizeof(dis));
	std::queue<int> q;
	q.push(0);

	vis[0] = 1, dis[0] = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (size_t i = 0; i < G[u].size(); i++) {
			int v = G[u][i].to, w = G[u][i].val;
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (!vis[v]) { vis[v] = 1; q.push(v); }
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> l >> r;
	for (int i = 1; i <= n; i++)
		std::cin >> w[i];
	std::sort(w + 1, w + n + 1);
	int bg = 1;
	for (int i = 1; i <= n; i++)
		if (w[i] != 0) {
			bg = i;
			break;
		}
	for (int i = 0; i < w[bg]; i++) {
		for (int j = 2; j <= n; j++)
			G[i].push_back({(i + w[j]) % w[bg], w[j]});
	}
	spfa();
	for (int i = 0; i < w[bg]; i++) {
		if (dis[i] <= r)
			ans += (r - dis[i]) / w[bg] + 1;
		if (dis[i] < l)
			ans -= (l - 1 - dis[i]) / w[bg] + 1;
	}
	std::cout << ans << "\n";
	return 0;
}
