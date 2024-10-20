#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e3 + 7;
constexpr int P = 1e5 + 3;

int a, b, c, d, k, ans;
int h[N], f[N][N];

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> a >> b >> c >> d >> k;
    f[0][0] = 1;
    for (int i = 1; i <= c; i++) {
        h[i] = d;
        f[i][0] = 1;
    }
    for (int i = 1; i <= a; i++) {
        h[c + i] = d + b;
        f[c + i][0] = 1;
    }
    for (int j = 1; j <= (a + c); j++) {
        for (int i = 1; i <= k; i++)
            f[j][i] = (f[j - 1][i] + f[j - 1][i - 1] * (h[j] - i + 1)) % P;
    }
    std::cout << f[a + c][k] << "\n";
    return 0;
}
