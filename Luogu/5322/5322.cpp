#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int M = 20007;

int s, n, m;
int ans, dp[M], a[N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> s >> n >> m;
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= n; j++)
            std::cin >> a[j][i];
    }
    for (int i = 1; i <= n; i++)
        std::sort(a[i] + 1, a[i] + s + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= 0; j--) {
            for (int k = 1; k <= s; k++)
                if (j > a[i][k] * 2)
                    dp[j] = std::max(dp[j], dp[j - a[i][k] * 2 - 1] + k * i);
        }
    }
    for (int i = 0; i <= m; i++)
        ans = std::max(ans, dp[i]);
    std::cout << ans << "\n";
    return 0;
}
