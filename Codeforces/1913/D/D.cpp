#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;
constexpr int R = std::numeric_limits<int>::max();
constexpr int P = 998244353;

int n, ans;
int tp, stc[N];
int l[N], r[N], a[N], p[N];
int f[N], g[N], qz[N];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> p[i];
    for (int i = 1; i <= n; i++) {
        while (tp && p[stc[tp]] > p[i])
            tp--;
        l[i] = stc[tp];
        stc[++tp] = i;
    }

    tp = 0;
    for (int i = n; i; i--) {
        while (tp && p[stc[tp]] > p[i])
            tp--;
        r[i] = stc[tp];
        stc[++tp] = i;
    }

    tp = 0;
    for (int i = 0; i <= n; i++)
        f[i] = g[i] = qz[i] = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!l[i])
            f[i]++;
        f[i] += qz[i - 1] - qz[l[i]];
        g[i] = f[l[i]] + g[l[i]];
        f[i] += g[i];
        qz[i] = qz[i - 1] + f[i];
        f[i] %= P;
        g[i] %= P;
        qz[i] %= P;
    }

    ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!r[i])
            (ans += f[i]) %= P;
    }

    std::cout << (ans + P) % P << "\n";
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("count.in", "r", stdin);
    // freopen("count.out", "w", stdout);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
