#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, m;
int t0t, ans, up;

struct edge {
	int to, val;
};

std::vector<edge> G[N << 1];
std::multiset<int> s[N];

int dfs(int u, int fa, int k) {
	s[u].clear();

	int vl;
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i].to, w = G[u][i].val;
		if (v == fa) continue;
		vl = dfs(v, u, k) + w;
		if (vl >= k)
			ans++;
		else
			s[u].insert(vl);
	}

	int mx = 0;
	while (!s[u].empty()) {
		if (s[u].size() == 1)
			return std::max(mx, *s[u].begin());
		auto it = s[u].lower_bound(k - *s[u].begin());
		if (it == s[u].begin() && s[u].count(*it) == 1)
			it++;
		if (it == s[u].end()) {
			mx = std::max(mx, *s[u].begin());
			s[u].erase(s[u].lower_bound(*s[u].begin()));
		} else {
			ans++;
			s[u].erase(s[u].lower_bound(*it));
			s[u].erase(s[u].lower_bound(*s[u].begin()));
		}
	}
	return mx;
}

bool check(int k) {
	ans = 0;
	dfs(1, 0, k);
	if (ans >= m)
		return 1;
	return 0;
}

int dfs1(int u, int fa) {
	int sum1 = 0, sum2 = 0;
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i].to, w = G[u][i].val;
		if (v == fa) continue;
		sum2 = std::max(sum2, dfs1(v, u) + w);
		if (sum1 < sum2)
			std::swap(sum1, sum2);
	}
	up = std::max(up, sum1 + sum2);
	return sum1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	dfs1(1, 0);

	int l = 1, r = up;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	std::cout << l << "\n";
	return 0;
}
