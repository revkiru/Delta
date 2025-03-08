#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

void solve() {
	int n, m;
	std::cin >> n >> m;
	bool cir = 0;
	std::vector<int> ind(n + 1), G[n << 1];
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		G[y].push_back(x);
		ind[x]++;
		if (x == y) { cir = 1; }
	}

	if (cir) { std::cout << "Impossible!\n"; return; }
	std::priority_queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (!ind[i])
			q.push(i);
	}

	int idx = 0;
	std::vector<int> ans(n + 1);
	while (q.size()) {
		int u = q.top();
		q.pop();
		ans[++idx] = u;
		for (auto v : G[u]) {
			ind[v]--;
			if (!ind[v])
				q.push(v);
		}
	}

	if (idx < n) { std::cout << "Impossible!\n"; return; }
	for (int i = n; i >= 1; i--)
		std::cout << ans[i] << " ";
	std::cout << "\n";
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
