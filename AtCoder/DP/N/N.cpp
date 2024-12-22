#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 407;

int n;
int a[N];
i64 sum[N], dp[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    memset(dp, 0x7f, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
        dp[i][i] = 0;
    }
    for (int len = 2; len <= n; len++) {
        for (int i = 1, j = 1; j <= n; i++) {
            j = i + len - 1;
            for (int k = i; k < j; k++)
                dp[i][j] = std::min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            dp[i][j] += sum[j] - sum[i - 1];
        }
    }
    std::cout << dp[1][n] << "\n";
    return 0;
}
