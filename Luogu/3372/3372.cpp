#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;
i64 a[N];

template <typename T>
struct node {
    T val, lzy;
};

template <typename T>
struct SegTree {
    node<T> tr[N << 2];

    void pushup(const T o) {
        tr[o].val = tr[o << 1].val + tr[o << 1 | 1].val;
    }

    void makeTag(T o, T l, T v) {
        tr[o].lzy += v;
        tr[o].val += l * v;
    }

    void pushdown(T o, T l, T r) {
        T mid = (l + r) >> 1;
        makeTag(o << 1, mid - l + 1, tr[o].lzy);
        makeTag(o << 1 | 1, r - mid, tr[o].lzy);
        tr[o].lzy = 0;
    }

    void build(T o, T l, T r) {
        if (l == r) { tr[o].val = a[l]; return; }
        T mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        pushup(o);
    }

    void update(T o, T l, T r, T ql, T qr, T v) {
        if (ql <= l && r <= qr) { makeTag(o, r - l + 1, v); return; }
        if (!((l > qr) || (r < ql))) {
            T mid = (l + r) >> 1;
            pushdown(o, l, r);
            update(o << 1, l, mid, ql, qr, v);
            update(o << 1 | 1, mid + 1, r, ql, qr, v);
            pushup(o);
        }
        return;
    }

    T query(T o, T l, T r, T ql, T qr) {
        if (ql <= l && r <= qr) { return tr[o].val; }
        if (!((l > qr) || (r < ql))) {
            T mid = (l + r) >> 1;
            pushdown(o, l, r);
            return (query(o << 1, l, mid, ql, qr) + query(o << 1 | 1, mid + 1, r, ql, qr));
        }
        return 0;
    }
};

SegTree<i64> seg;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    
    seg.build(1, 1, n);
    while (m--) {
        int op, x, y;
        i64 k;
        std::cin >> op;
        if (op == 1) {
            std::cin >> x >> y >> k;
            seg.update(1, 1, n, x, y, k);
        } else {
            std::cin >> x >> y;
            std::cout << seg.query(1, 1, n, x, y) << "\n";
        }
    }
    return 0;
}
