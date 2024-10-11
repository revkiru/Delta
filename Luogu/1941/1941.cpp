#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 10007;
constexpr int inf = 0x3f3f3f3f;

int n, m, k;
int x[N], y[N], dp[N][1007];
int low[N], hgh[N], pex[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> k;
    memset(dp, inf, sizeof(dp));
    for (int i = 1; i <= n; i++) {
        low[i] = 0;
        hgh[i] = m + 1;
        pex[i] = 0;
    }
    for (int i = 1; i <= n; i++)
        std::cin >> x[i] >> y[i];
    for (int i = 1; i <= k; i++) {
        int a, b, c;
        std::cin >> a >> b >> c;
        low[a] = b;
        hgh[a] = c;
        pex[a] = 1;
    }
    for (int i = 1; i <= m; i++)
        dp[0][i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            dp[i][std::min(m, j + x[i])] = std::min({dp[i][std::min(m, j + x[i])], dp[i - 1][j] + 1, dp[i][j] + 1});
        for (int j = 1; j <= m - y[i]; j++)
            dp[i][j] = std::min(dp[i][j], dp[i - 1][j + y[i]]);
        for (int j = 0; j <= low[i]; j++)
            dp[i][j] = inf;
        for (int j = hgh[i]; j <= m; j++)
            dp[i][j] = inf;
    }

    int ans = inf, ret = -1;
    for (int i = 1; i <= m; i++)
        ans = std::min(ans, dp[n][i]);
    if (ans < inf) { std::cout << "1\n" << ans << "\n"; exit(0); }

    ans = 0;
    for (int i = n; i >= 1; i--) {
        if (ret != -1) break;
        for (int j = 1; j <= m; j++)
            if (dp[i][j] < inf)
                ret = i;
    }
    for (int i = 1; i <= ret; i++)
        ans += pex[i];
    std::cout << "0\n";
    std::cout << ans << "\n";
    return 0;
}
