#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 15;

i64 a, b;
i64 f[N], p[N], pw[N], nw[N];

i64 dfs(int u, int x, bool f0, bool lim) {
    /* 位数、x、前导 0、贴上界 */
    if (!u) { if (f0) f0 = 0; return 0; }
    if (!lim && !f0 && (~f[u])) { return f[u]; }
    i64 cnt = 0;
    int lst = lim ? p[u] : 9;
    for (int i = 0; i <= lst; i++) {
        if (f0 && i == 0)
            cnt += dfs(u - 1, x, 1, lim && i == lst);
        else if (i == x && lim && i == lst)
            cnt += nw[u - 1] + 1 + dfs(u - 1, x, 0, lim && i == lst);
        else if (i == x)
            cnt += pw[u - 1] + dfs(u - 1, x, 0, lim && i == lst);
        else
            cnt += dfs(u - 1, x, 0, lim && i == lst);
    }
    if ((!lim) && (!f0)) f[u] = cnt;
    return cnt;
}

i64 ans(i64 d, i64 dig) {
    int len = 0;
    memset(f, -1, sizeof(f));
    while (d) {
        p[++len] = d % 10;
        d /= 10;
        nw[len] = nw[len - 1] + p[len] * pw[len - 1];
    }
    return dfs(len, dig, 1, 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> a >> b;
    pw[0] = 1;
    for (int i = 1; i <= 12; i++)
        pw[i] = 1ll * 10 * pw[i - 1];
    for (int i = 0; i < 10; i++)
        std::cout << ans(b, i) - ans(a - 1, i) << " ";
    std::cout << "\n";
    return 0;
}
