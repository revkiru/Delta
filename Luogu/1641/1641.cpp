#include <bits/stdc++.h>

#define int long long

constexpr int P = 20100403;

int n, m;
int u, d, ans;

template <typename T>
T expow(T a, T b) {
    T ret = 1 % P;
    for (; b; b >>= 1) {
        if (b & 1)
            ret = 1ll * ret * a % P;
        a = 1ll * a * a % P;
    }
    return ret;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    u = d = 1;
    for (int i = m + 1; i <= n + m; i++)
        u = u * i % P * expow<int>(i - m, P - 2) % P;
    for (int i = m; i <= n + m; i++)
        d = d * i % P * expow<int>(i - m + 1, P - 2) % P;
    ans = ((u - d) % P + P) % P;
    std::cout << ans << "\n";
    return 0;
}
