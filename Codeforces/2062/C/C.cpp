#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<i64> a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}

	int m = n;
	i64 ans = 50 * -1000;
	for (int c = 0; c < n; c++) {
		i64 res = 0;
		for (int i = 1; i <= m; i++)
			res += a[i];
		if (c != 0)
			ans = std::max({ans, res, -res});
		else
			ans = std::max({ans, res});
		for (int i = 1; i < m; i++)
			a[i] = a[i + 1] - a[i];
		m--;
	}
	std::cout << ans << "\n";
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
