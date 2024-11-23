#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::set<int> e[(n + m) << 1];
	for (int i = 1; i <= m; i++) {
		int x, y;
		std::cin >> x >> y;
		e[x].insert(y);
		e[y].insert(x);
	}

	int cnt = 0;
	std::vector<std::tuple<int, int, int>> ans(std::max(n, m) << 1 | 1);
	for (int i = 2; i <= n; i++) {
		while (e[i].size()) {
			int x = *e[i].rbegin();
			if (x == 1)
				break;
			e[i].erase(x);
			e[x].erase(i);
			if (e[1].count(i)) {
				e[1].erase(i);
				e[i].erase(1);
			} else {
				e[1].insert(i);
				e[i].insert(1);
			}
			if (e[1].count(x)) {
				e[1].erase(x);
				e[x].erase(1);
			} else {
				e[1].insert(x);
				e[x].insert(1);
			}
			ans[++cnt] = {1, i, x};
		}
	}

	if (e[1].size()) {
		int x = 1, y = *e[1].begin();
		for (int i = 2; i <= n; i++) {
			if (e[i].size())
				continue;
			ans[++cnt] = {x, y, i};
			x = i;
		}
	}

	std::cout << cnt << "\n";
	for (int i = 1; i <= cnt; i++) {
		std::cout << std::get<0>(ans[i]) << " " << std::get<1>(ans[i]) << " " << std::get<2>(ans[i]) << "\n";
	}
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
