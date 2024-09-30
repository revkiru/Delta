#include <bits/stdc++.h>

#define int long long

constexpr int N = 5e5 + 7;
constexpr int R = 1e18;

int n, m;
int a[N], b[N];

struct node {
    int a, b, lmx, rmx, ans;    
};

node operator + (const node &x, const node &y) {
    node t;
    t.a = std::max(x.a, y.a);
    t.b = std::min(x.b, y.b);
    t.lmx = std::max({x.lmx, y.lmx, x.a - y.b});
    t.rmx = std::max({x.rmx, y.rmx, y.a - x.b});
    t.ans = std::max({x.ans, y.ans, x.lmx + y.a, x.a + y.rmx});
    return t;
}

struct SegTree {
    node tr[N << 2];

    void pushup(int o) {
        node x = tr[o << 1], y = tr[o << 1 | 1];
        tr[o].a = std::max(x.a, y.a);
        tr[o].b = std::min(x.b, y.b);
        tr[o].lmx = std::max({x.lmx, y.lmx, x.a - y.b});
        tr[o].rmx = std::max({x.rmx, y.rmx, y.a - x.b});
        tr[o].ans = std::max({x.ans, y.ans, x.lmx + y.a, x.a + y.rmx});
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o].a = a[l];
            tr[o].b = b[l];
            tr[o].lmx = tr[o].rmx = tr[o].ans = -R;
            return;
        }
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        pushup(o);
    }

    void update1(int o, int l, int r, int ql, int qr) {
        if (l == r) { tr[o].a = qr; return; }
        int mid = (l + r) >> 1;
        if (ql <= mid) update1(o << 1, l, mid, ql, qr);
        else update1(o << 1 | 1, mid + 1, r, ql, qr);
        pushup(o);
    }

    void update2(int o, int l, int r, int ql, int qr) {
        if (l == r) { tr[o].b = qr; return; }
        int mid = (l + r) >> 1;
        if (ql <= mid) update2(o << 1, l, mid, ql, qr);
        else update2(o << 1 | 1, mid + 1, r, ql, qr);
        pushup(o);
    }

    node query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[o];
        int mid = (l + r) >> 1;
        if (mid >= qr) return query(o << 1, l, mid, ql, qr);
        if (mid < ql) return query(o << 1 | 1, mid + 1, r, ql, qr);
        return query(o << 1, l, mid, ql, qr) + query(o << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
        std::cin >> b[i];
    seg.build(1, 1, n);
    while (m--) {
        int op, l, r;
        std::cin >> op >> l >> r;
        if (op == 1)
            seg.update1(1, 1, n, l, r);
        if (op == 2)
            seg.update2(1, 1, n, l, r);
        if (op == 3)
            std::cout << seg.query(1, 1, n, l, r).ans << "\n";
    }
    return 0;
}
