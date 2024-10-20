#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;
constexpr int P = 1e9 + 7;

int n, ans;
int f[N], s[N << 1];

struct node {
    int l, r;

    friend bool operator < (const node &x, const node &y) {
        if (x.l == y.l)
            return x.r < y.r;
        return x.l < y.l;
    }
} a[N];

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

    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i].l >> a[i].r;
    std::sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++)
        s[a[i].r]++;
    for (int i = 1; i <= (n << 1); i++)
        s[i] = (s[i - 1] + s[i]) % P;
    for (int i = 1; i <= n; i++) {
        int x = s[a[i].l - 1];
        f[i] = (f[i] + 2 * f[i - 1]) % P;
        f[i] = (f[i] + expow<int>(2, x) % P) % P;
    }
    std::cout << f[n] << "\n";
    return 0;
}
