#include <bits/stdc++.h>

#define int long long

constexpr int N = 12;
constexpr int P = 1e8;

int n, m;
int _f[15], g[1 << N], h[1 << N];
int a[15][15], f[15][1 << N];

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            std::cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)    
            _f[i] = (_f[i] << 1) + a[i][j];
    }
    for (int i = 0; i < (1 << m); i++) {
        if (!(i & (i >> 1)) && !(i & (i << 1))) {
            g[i] = 1;
            if ((i & _f[1]) == i)
                f[1][i] = 1;
        }
    }
    for (int x = 2; x <= n; x++) {
        for (int j = 0; j < (1 << m); j++)
            if ((j & _f[x - 1]) == j && g[j])
                for (int k = 0; k < (1 << m); k++)
                    if (((k & _f[x]) == k ) && !(j & k) && g[k])
                        f[x][k] = (f[x][k] + f[x - 1][j]) % P;
    }
    int ans = 0;
    for (int i = 0; i < (1 << m); i++)
        ans = (ans + f[n][i]) % P;
    std::cout << ans << "\n";
    return 0;
}
