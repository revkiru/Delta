#include <bits/stdc++.h>

#define int long long

constexpr int N = 1007;
constexpr int P = 10007;

int a, b, k, n, m;
int c[N][N];

template <typename T>
T expow(T a, T b, const T P) {
    T ret = 1 % P;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = 1ll * ret * a % P;
        a = 1ll * a * a % P;
    }
    return ret;
}

int dfs(int n, int m) {
    if (!m) return c[n][m] = 1;
    if (m == 1) { return c[n][m] = n; }
    if (c[n][m]) { return c[n][m]; }
    if (n - m < m) { m = n - m; }
    return c[n][m] = (dfs(n - 1, m) + dfs(n - 1, m - 1)) % P;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> a >> b >> k >> n >> m;
    c[1][0] = c[1][1] = 1;
    a %= P, b %= P;

    int ans = 1;
    ans *= (expow<int>(a, n, P) * expow<int>(b, m, P) + P) % P;
    if (n > m) n = m;
    ans *= dfs(k, n) % P;
    std::cout << ans % P << "\n";
    return 0;
}
