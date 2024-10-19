#include <bits/stdc++.h>

#define int long long

constexpr int P = 100003;

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

int m, n;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> m >> n;
    int ans = ((expow<int>(m, n, P) + P) % P - ((m % P) * expow<int>(m - 1, n - 1, P) + P) % P + P) % P;
    std::cout << ans << "\n";
    return 0;
}
