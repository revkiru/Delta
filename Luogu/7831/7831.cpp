#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int inf = 1e9;

int n, m;
int vis[N], ind[N], ans[N];

struct edge {
	int u, v, r, p, id;

	bool operator < (const edge &rhs) const {
		return r > rhs.r;
	}
};

std::pair<int, int> vec[N];
std::vector<edge> E;
std::vector<std::pair<int, int>> G[N << 1];
std::queue<int> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, u, v, r, p; i <= m; i++) {
		std::cin >> u >> v >> r >> p;
		G[v].push_back({u, i});
		vec[i] = {p, r};
		ind[u]++;
		E.push_back({v, u, r, p, i});
	}
	memset(ans, 0x3f, sizeof(ans));
	for (int i = 1; i <= n; i++) {
		if (!ind[i])
			q.push(i);
	}
	std::sort(E.begin(), E.end());
	for (auto i : E) {
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (auto v : G[u]) {
				if (vis[v.second])
					continue;
				vis[v.second] = 1;
				if (ans[u] < inf)
					ans[v.first] = std::min(ans[v.first], std::max(vec[v.second].second, ans[u] - vec[v.second].first));
				ind[v.first]--;
				if (!ind[v.first])
					q.push(v.first);
			}
		}
		if (!vis[i.id]) {
			vis[i.id] = 1;
			ans[i.v] = std::min(ans[i.v], i.r);
			ind[i.v]--;
			if (!ind[i.v])
				q.push(i.v);
		}
	}
	for (int i = 1; i <= n; i++)
		std::cout << (ans[i] > 1e9 ? -1 : ans[i]) << " ";
	std::cout << "\n";
	return 0;
}
