#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int inf = 1e9;

int n;
int a[N << 1], sum[N << 1];
int dp1[N << 1][N << 1], dp2[N << 1][N << 1];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i + n] = a[i];
	}

	sum[0] = 0;
	memset(dp1, 0, sizeof(dp1));
	memset(dp2, 0x3f, sizeof(dp2));
	for (int i = 1; i <= n * 2; i++) {
		dp1[i][i] = dp2[i][i] = 0;
		sum[i] = sum[i - 1] + a[i];
	}

	for (int len = 2; len <= n; len++) {
		for (int l = 1, r = l + len - 1; l <= n * 2; l++) {
			r = l + len - 1;
			if (r > n * 2)
				continue;
			dp1[l][r] = -inf;
			dp2[l][r] = inf;
			for (int k = l; k < r; k++) {
				dp1[l][r] = std::max(dp1[l][r], dp1[l][k] + dp1[k + 1][r] + (sum[r] - sum[l - 1]));
				dp2[l][r] = std::min(dp2[l][r], dp2[l][k] + dp2[k + 1][r] + (sum[r] - sum[l - 1]));
			}
		}
	}

	int maxAns = -inf, minAns = inf;
	for (int i = 1; i <= n; i++) {
		maxAns = std::max(maxAns, dp1[i][i + n - 1]);
		minAns = std::min(minAns, dp2[i][i + n - 1]);
	}

	std::cout << minAns << "\n" << maxAns << "\n";
	return 0;
}
