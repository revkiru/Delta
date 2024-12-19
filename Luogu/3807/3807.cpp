#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, p;
i64 fac[N];

void init(const int P) {
    fac[0] = 1;
    for (int i = 1; i <= P; i++) {
        fac[i] = fac[i - 1] * i % P;
    }
}

template <typename T>
T expow(T a, T b, const T P) {
    T ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = ret * a % P;
        a = a * a % P;
    }
    return ret;
}

i64 C(i64 n, i64 m) {
    if (m > n) return 0;
    return ((fac[n] * expow<i64>(fac[m], p - 2, p)) % p * expow<i64>(fac[n - m], p - 2, p) % p);
}

i64 Lucas(i64 n, i64 m, const i64 P) {
    if (!m) return 1;
    return C(n % P, m % P) * Lucas(n / P, m / P, P) % P;
}

void solve() {
    scanf("%d %d %d", &n, &m, &p);
    init(p);
    printf("%lld\n", Lucas(n + m, n, p));
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        solve();
    }
    return 0;
}
