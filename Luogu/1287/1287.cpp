#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;

int n, r;
int f[N][N];

int fac(int n) {
    int ret = 1;
    for (int i = 2; i <= n; i++)
        ret *= i;
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> r;
    f[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= r; j++)
            f[i][j] = f[i - 1][j - 1] + f[i - 1][j] * j;
    }
    std::cout << 1ll * f[n][r] * fac(r) << "\n";
    return 0;
}
