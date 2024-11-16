#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	i64 n;
	int m;
	std::cin >> n >> m;
	std::vector<std::pair<i64, i64>> x(m + 1);
	for (int i = 1; i <= m; i++) {
		std::cin >> x[i].first;
	}
	i64 sum = 0;
	for (int i = 1; i <= m; i++) {
		std::cin >> x[i].second;
		sum += x[i].second;
	}
	std::sort(x.begin() + 1, x.end());
	if (x[1].first != 1) { std::cout << "-1\n"; return; }
	if (sum != n) { std::cout << "-1\n"; return; }
	if (x[m].first != n) { x[++m].first = n; }
	i64 ans = 0;
	for (int i = 2; i <= m; i++) {
		if (x[i - 1].second < x[i].first - x[i - 1].first) { std::cout << "-1\n"; return; }
		ans += (x[i].first - x[i - 1].first) * (x[i].first - x[i - 1].first - 1) / 2;
		x[i - 1].second -= x[i].first - x[i - 1].first;
		if (x[i - 1].first > 0) {
			ans += x[i - 1].second * (x[i].first - x[i - 1].first);
			x[i].second += x[i - 1].second;
		}
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
