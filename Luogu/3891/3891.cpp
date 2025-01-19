#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e2 + 7;
constexpr int T = 1e3 + 7;

int n, m, t;
i64 a[N], b[N], f[T][T];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> t;
	memset(f, 0x3f, sizeof(f));
	for (int i = 0; i <= t; i++)
		f[t][i] = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i] >> b[i];
	}
	for (int j = t; ~j; j--) {
		for (int i = t; ~i; i--) {
			if (i == t)
				continue;
			if (i + j <= t)
				f[i][j] = f[i + j][j] + 1;
			else
				f[i][j] = 1;
			for (int k = 1; k <= n; k++) {
				if (i - a[k] >= 0 && j + b[k] <= t)
					f[i][j] = std::min(f[i][j], f[i - a[k]][j + b[k]]);
				else if (i - a[k] >= 0)
					f[i][j] = std::min(f[i][j], (i64) 1);
			}
		}
	}
	i64 ans = std::numeric_limits<i64>::max();
	for (int i = 0; i <= m; i++)
		ans = std::min(ans, f[i][0]);
	std::cout << ans << "\n";
	return 0;
}
