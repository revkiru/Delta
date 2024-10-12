#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4507;

int n, p;
int dp[N][2], sum[N][2];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> p;
    const int P = p;
    dp[1][0] = dp[2][1] = 1;
    for (int i = 3; i <= n; i++) {
        for (int j = 1; j < i; j++) {
            sum[j][0] = (sum[j - 1][0] + dp[j][0]) % P;
            sum[j][1] = (sum[j - 1][1] + dp[j][1]) % P;
        }
        for (int j = 1; j <= i; j++) {
            dp[j][0] = (sum[i - 1][1] - sum[j - 1][1] + P) % P;
            dp[j][1] = sum[j - 1][0];
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = (ans + (dp[i][0] + dp[i][1]) % P) % P;
    std::cout << ans << "\n";
    return 0;
}
