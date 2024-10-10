#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int inf = 0x3f3f3f3f;

int t, n, k;
int a[N], pos[N], nex[N][2];
i64 f[N][2];

struct Fenwick {
    int tr[N << 1];

    void clear() {
        for (int i = 0; i <= n; i++)
            tr[i] = 0;
    }

    int lowbit(int x) { return x & -x; }

    void add(int i, int x) {
        for (; i <= n; i += lowbit(i))
            tr[i] += x;
    }

    int sum(int x) {
        int res = 0;
        for (int i = x; i; i -= lowbit(i))
            res += tr[i];
        return res;
    }

    int kth(int x) {
        int rk = 0;
        for (int i = 1 << (std::__lg(n)); i; i >>= 1) {
            if (rk + i <= n && x > tr[rk + i]) {
                rk += i;
                x -= tr[rk];
            }
        }
        return rk + 1;
    }
} bit;

int calc(int x, int p) { return std::min(std::abs(x - p), n - (std::abs(x - p))); }

int rank(int x) { return bit.kth(bit.sum(x) + 1); }

i64 solve() {
    if (n == k)
        return 0;
    bit.clear();
    bit.add(n + 1, 1);
    for (int i = k + 1; i <= n; i++)
        bit.add(a[i], 1);
    nex[a[1]][0] = rank(a[1]);
    nex[a[k]][1] = rank(a[k]);
    int st = bit.kth(1);
    for (int i = 2; i <= n; i++) {
        int p = i + k - 1;
        if (p > n) p -= n;
        bit.add(a[p], -1);
        bit.add(a[i - 1], 1);
        nex[a[i]][0] = rank(a[i]);
        nex[a[p]][1] = rank(a[p]);
    }
    for (int v = n; v >= 1; v--) {
        for (int p = 0; p <= 1; p++) {
            int mv = nex[v][p];
            if (mv > n) { f[v][p] = 0; continue; }
            int u = (p == 0) ? 1 : k;
            int np = pos[mv] - pos[v];
            if (np < 0) np += n;
            np += u;
            if (np > n) np -= n;
            f[v][p] = std::min(f[mv][0] + calc(np, 1), f[mv][1] + calc(np, k));
        }
    }
    return std::min(f[st][0] + calc(pos[st], 1), f[st][1] + calc(pos[st], k));
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i = 1; i <= n; i++) {
            f[i][0] = f[i][1] = -1;
            nex[i][0] = nex[i][1] = n + 1;
            scanf("%d", &a[i]);
            pos[a[i]] = i;
        }
        printf("%lld\n", solve());
    }
    return 0;
}
