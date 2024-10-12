#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 57;

int n, c;
int pos[N], pwr[N], s[N];
i64 dp[N][N][2];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> c;
    for (int i = 1; i <= n; i++) {
        std::cin >> pos[i] >> pwr[i];
        s[i] = s[i - 1] + pwr[i];
    }
    memset(dp, 0x7f, sizeof(dp));
    dp[c][c][0] = dp[c][c][1] = 0;
    for (int i = c; i <= n; i++) {
        for (int j = i - 1; j; j--) {
            int sum = s[n] + s[j - 1] - s[i];
            dp[j][i][0] = std::min(dp[j][i][0], dp[j + 1][i][0] + (sum + pwr[j]) * (pos[j + 1] - pos[j]));
            dp[j][i][0] = std::min(dp[j][i][0], dp[j + 1][i][1] + (sum + pwr[j]) * (pos[i] - pos[j]));
            dp[j][i][1] = std::min(dp[j][i][1], dp[j][i - 1][1] + (sum + pwr[i]) * (pos[i] - pos[i - 1]));
            dp[j][i][1] = std::min(dp[j][i][1], dp[j][i - 1][0] + (sum + pwr[i]) * (pos[i] - pos[j]));
        }
    }
    std::cout << std::min(dp[1][n][0], dp[1][n][1]) << "\n";
    return 0;
}
