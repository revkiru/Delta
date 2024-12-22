#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3007;
constexpr int P = 1e9 + 7;

int n;
std::string s;
i64 dp[N][N], sum[N][N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	std::cin >> s;

	s = '$' + s;
	dp[1][1] = 1;
	for (int i = 1; i <= n; i++)
		sum[1][i] = 1;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			if (s[i - 1] == '<')
				dp[i][j] = sum[i - 1][j - 1] % P;
			if (s[i - 1] == '>')
				dp[i][j] = (sum[i - 1][i - 1] - sum[i - 1][j - 1] + P) % P;
			sum[i][j] = (sum[i][j - 1] + dp[i][j]) % P;
		}
	}
	std::cout << (sum[n][n] % P) << "\n";
	return 0;
}
