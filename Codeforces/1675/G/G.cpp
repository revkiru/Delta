#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 300;
constexpr int inf = std::numeric_limits<int>::max();

int n, m;
int a[N], sum[N];
int f[N][N][N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    memset(f, 0x3f, sizeof(f));
    f[0][0][m] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= m; j++) {
            int mnx = inf;
            for (int k = m; k >= 0; k--) {
                mnx = std::min(f[i][j][k], mnx);
                if (j + k <= m)
                    f[i + 1][j + k][k] = std::min(mnx + std::abs(j + k - sum[i + 1]), f[i + 1][j + k][k]);
            }
        }
    }

    int ans = inf;
    for (int i = 0; i <= m; i++)
        ans = std::min(f[n][m][i], ans);
    std::cout << ans << "\n";
    return 0;
}
