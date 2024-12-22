#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 25;
constexpr int P = 1e9 + 7;

int n;
bool a[N][N];
i64 dp[N << 1][1 << 22];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			std::cin >> a[i][j];
	}

	dp[0][0] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if (__builtin_popcount(j) == i) {
				for (int k = 0; k < n; k++) {
					if (a[i][k] && !(j & (1 << k))) {
						dp[i + 1][j | (1 << k)] = (dp[i + 1][j | (1 << k)] + dp[i][j]) % P;
					}
				}
			}
		}
	}
	std::cout << dp[n][(1 << n) - 1] << "\n";
	return 0;
}
