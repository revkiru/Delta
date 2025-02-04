#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, m, len;
int a[N], lsh[N];

struct node {
    int ls, rs, val;
    i64 sum;
};

struct PersistentSegTree {
    int rcnt, rt[N];
    node tr[N << 5];

    #define ls(o) (tr[o].ls)
    #define rs(o) (tr[o].rs)

    int build(int l, int r) {
        int o = ++rcnt;
        if (l == r) return rcnt;
        int mid = (l + r) >> 1;
        ls(o) = build(l, mid);
        rs(o) = build(mid + 1, r);
        return rcnt;
    }

    int update(int o, int l, int r, int k) {
        int dir = ++rcnt;
        ls(dir) = ls(o), rs(dir) = rs(o), tr[dir].sum = tr[o].sum + 1;
        if (l == r) return dir;
        int mid = (l + r) >> 1;
        if (k <= mid)
            ls(dir) = update(ls(dir), l, mid, k);
        else
            rs(dir) = update(rs(dir), mid + 1, r, k);
        return dir;
    }

    int query(int l, int r, int ql, int qr, int k) {
        int mid = (l + r) >> 1, x = tr[tr[qr].ls].sum - tr[tr[ql].ls].sum;
        if (l == r) return l;
        if (k <= x)
            return query(l, mid, ls(ql), ls(qr), k);
        else
            return query(mid + 1, r, rs(ql), rs(qr), k - x);
    }
} pSeg;

int GetId(const int &x) {
    return std::lower_bound(lsh + 1, lsh + len + 1, x) - lsh;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        lsh[i] = a[i];
    }
    std::sort(lsh + 1, lsh + n + 1);
    len = std::unique(lsh + 1, lsh + n + 1) - lsh - 1;
    pSeg.rt[0] = pSeg.build(1, len);
    for (int i = 1; i <= n; i++)
        pSeg.rt[i] = pSeg.update(pSeg.rt[i - 1], 1, len, GetId(a[i]));

    for (int i = 1, l, r, k; i <= m; i++) {
        std::cin >> l >> r >> k;
        std::cout << lsh[pSeg.query(1, len, pSeg.rt[l - 1], pSeg.rt[r], k)] << "\n";
    }
    return 0;
}
