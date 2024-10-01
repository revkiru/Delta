#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;

int n, m;
int a[N];

struct node {
    int val, mxn;
};

struct SegTree {
    node tr[N << 2];

    void pushup(int o) {
        tr[o].val = tr[o << 1].val + tr[o << 1 | 1].val;
        tr[o].mxn = std::max(tr[o << 1].mxn, tr[o << 1 | 1].mxn);
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o].val = tr[o].mxn = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        pushup(o);
    }

    void modUpdate(int o, int l, int r, int ql, int qr, const int P) {
        if (tr[o].mxn < P) return;
        if (l == r) {
            tr[o].val %= P;
            tr[o].mxn %= P;
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            modUpdate(o << 1, l, mid, ql, qr, P);
        if (qr > mid)
            modUpdate(o << 1 | 1, mid + 1, r, ql, qr, P);
        pushup(o);
    }

    void valUpdate(int o, int l,int r, int p, int v) {
        if (l == r) {
            tr[o].val = tr[o].mxn = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            valUpdate(o << 1, l, mid, p, v);
        else
            valUpdate(o << 1 | 1, mid + 1, r, p, v);
        pushup(o);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].val;
        int ret = 0;
        int mid = (l + r) >> 1;
        if (ql <= mid)
            ret += query(o << 1, l, mid, ql, qr);
        if (qr > mid)
            ret += query(o << 1 | 1, mid + 1, r, ql, qr);
        return ret;
    }
} seg;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    seg.build(1, 1, n);
    while (m--) {
        int opt, l, r, x;
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> l >> r;
            std::cout << seg.query(1, 1, n, l, r) << "\n";
        }
        if (opt == 2) {
            std::cin >> l >> r >> x;
            seg.modUpdate(1, 1, n, l, r, x);
        }
        if (opt == 3) {
            std::cin >> l >> x;
            seg.valUpdate(1, 1, n, l, x);
        }
    }
    return 0;
}
