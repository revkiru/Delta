#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int M = 30;

int n;
i64 ans, a[M][N];

i64 f(i64 k) {	// according to the material: the f function
	i64 ret = 0;
	while (k != 0) {
		ret += k % 10;
		k /= 10;
	}
	return ret;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("digit.in", "r", stdin);
	// freopen("digit.out", "w", stdout);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		i64 inp, u = 10;
		std::cin >> inp;
		for (int p = 1; p <= 15; p++) {
			a[p][i] = inp % u;
			u *= 10;
		}
		ans += 2 * n * f(inp);
	}


	i64 u = 1;
	std::function<i64(int, int)> d = [&](int i, int j) {	// 9 * d(a, b)
		return 9 * (a[i] + n + 1 - std::lower_bound(a[i] + 1, a[i] + n + 1, u - a[i][j]));
	};

	for (int i = 1; i <= 15; i++) {
		u *= 10;
		std::sort(a[i] + 1, a[i] + n + 1);
		for (int j = 1; j <= n; j++) {
			ans -= d(i, j);
		}
	}

	std::cout << ans << "\n";
	return 0;
}
