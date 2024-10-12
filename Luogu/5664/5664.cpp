/* 很妙的优化，仅仅只是移了一下项 */

#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int M = 2e3 + 7;
constexpr int P = 998244353;

int n, m;
i64 s[N];
i64 a[N][M], g[N][N], f[N][N << 1];

i64 A(int y, int x) { return (s[y] - a[y][x] + P) % P; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> a[i][j];
            s[i] = (s[i] + a[i][j]) % P;
        }
    }

    i64 s1 = 0, s2 = 0;
    for (int x = 1; x <= m; x++) {
        memset(f, 0, sizeof(f));
        f[0][n] = 1;
        for (int y = 1; y <= n; y++) {
            for (int j = n - y; j <= n + y; j++)
                if (j - 1 > 0)
                    f[y][j] = (f[y - 1][j] + f[y - 1][j - 1] * a[y][x] % P + f[y - 1][j + 1] * A(y, x) % P) % P;
        }
        for (int i = 1; i <= n; i++)
            s1 = (s1 + f[n][n + i]) % P;
    }

    g[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            g[i][j] = g[i - 1][j];
            if (j > 0)
                g[i][j] = (g[i][j] + g[i - 1][j - 1] * s[i] % P) % P;
        }
    }
    for (int i = 1; i <= n; i++)
        s2 = (s2 + g[n][i]) % P;

    std::cout << (s2 - s1 + P) % P << "\n";
    return 0;
}
