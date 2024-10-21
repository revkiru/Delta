#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;
constexpr int P = 1e8 + 7;

int n, m;
int fc = 1, inv = 1;
int A[N], f[N];

template <typename T>
T expow(T a, T b) {
    T ret = 1;
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
    A[0] = 1;
    f[0] = 1;
    f[1] = 0;

    for (int i = 1; i <= n; i++)
        fc = fc * 2 % P;
    for (int i = 1; i <= m; i++)
        inv = inv * i % P;
    for (int i = 1; i <= m; i++)
        A[i] = A[i - 1] * (fc - i + P) % P;
    for (int i = 2; i <= m; i++)
        f[i] = ((A[i - 1] - f[i - 1] - f[i - 2] * (i - 1) % P * (fc - 1 - (i - 2)) % P) % P + P) % P;
    std::cout << f[m] * expow<int>(inv, P - 2) % P << "\n";
    return 0;
}
