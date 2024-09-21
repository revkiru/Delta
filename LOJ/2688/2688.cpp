#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 57;
constexpr int M = 4007;

int n, m, t0t;
int a[M], b[M], c[M], d[M], ps[M];
int g[N][M], f[N][N][M], pr[N][N][M], mx[N][N][M];

void getrc(int l, int r, int k) {
    if (l > r) return;
    k = pr[l][r][k];
    int pos = f[l][r][k];
    ps[pos] = d[k];
    getrc(l, pos - 1, k);
    getrc(pos + 1, r, k);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i] >> b[i] >> c[i];
        d[i] = c[i];
    }

    std::sort(d + 1, d + m + 1);
    t0t = std::unique(d + 1, d + m + 1) - d - 1;
    for (int i = 1; i <= m; i++)
        c[i] = std::lower_bound(d + 1, d + t0t + 1, c[i]) - d;

    for (int i = n; i; i--) {
        for (int j = i; j <= n; j++) {
            for (int k = i; k <= j; k++) {
                for (int l = 0; l <= t0t; l++)
                    g[k][l] = 0;
            }
            for (int k = 1; k <= m; k++) {
                if (i <= a[k] && b[k] <= j)
                    for (int l = a[k]; l <= b[k]; l++)
                        g[l][c[k]]++;
            }
            for (int k = i; k <= j; k++) {
                for (int l = t0t - 1; l; l--)
                    g[k][l] += g[k][l + 1];
            }
            for (int k = t0t; k; k--) {
                int mxn = 0;
                for (int l = i; l <= j; l++) {
                    int w = mx[i][l - 1][k] + mx[l + 1][j][k] + g[l][k] * d[k];
                    if (mxn <= w) { mxn = w; f[i][j][k] = l; }
                }
                if (mxn >= mx[i][j][k + 1]) {
                    mx[i][j][k] = mxn;
                    pr[i][j][k] = k;
                } else {
                    mx[i][j][k] = mx[i][j][k + 1];
                    pr[i][j][k] = pr[i][j][k + 1];
                }
            }
        }
    }

    getrc(1, n, 1);
    std::cout << mx[1][n][1] << "\n";
    for (int i = 1; i <= n; i++)
        std::cout << ps[i] << " ";
    std::cout << "\n";
    return 0;
}
