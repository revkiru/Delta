#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 507;

int n, ans;
int dp[N][N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> dp[i][i];
		ans = std::max(ans, dp[i][i]);
	}

	for (int len = 2; len <= n; len++) {
		for (int l = 1, r = len; r <= n; l++, r++) {
			for (int k = l; k < r; k++) {
				if (dp[l][k] && dp[k + 1][r] && dp[l][k] == dp[k + 1][r]) {
					dp[l][r] = dp[l][k] + dp[k + 1][r];
					break;
				}
			}
			for (int k = l, t = r; k < t - 1; ) {
				if (dp[l][r])
					break;
				if (!dp[l][k])
					k++;
				else if (!dp[t][r])
					t--;
				else if (dp[l][k] == dp[t][r]) {
					if (dp[k + 1][t - 1])
						dp[l][r] = dp[l][k] + dp[k + 1][t - 1] + dp[t][r];
					else { k++; t--; }
				}
				else if (dp[l][k] < dp[t][r])
					k++;
				else if (dp[l][k] > dp[t][r])
					t--;
			}
			ans = std::max(ans, dp[l][r]);
		}
	}

	std::cout << ans << "\n";
	return 0;
}
