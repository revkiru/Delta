#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;

int n;
int a[N << 1], f[N << 2][N << 2];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 2; i <= n + 1; i++) {
        for (int l = 1; l + i - 1 <= (n << 1); l++) {
            int r = l + i - 1;
            for (int k = l + 1; k <= l + i - 2; k++)
                f[l][r] = std::max(f[l][r], f[l][k] + f[k][r] + (a[l] * a[k] * a[r]));
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = std::max(ans, f[i][n + i]);
    std::cout << ans << "\n";
    return 0;
}
