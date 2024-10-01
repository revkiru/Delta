#include <bits/stdc++.h>

using i64 = long long;
using f64 = double;

constexpr int N = 1e5 + 7;

int n, m;

struct node {
    f64 mx;
    int ans;
};

struct SegTree {
    node tr[N << 2];

    int query(int o, int l, int r, f64 mx) {
        if (tr[o].mx <= mx) return 0;
        if (l == r) return tr[o].mx > mx;
        else if (tr[o << 1].mx <= mx) return query(o << 1 | 1, ((l + r) >> 1) + 1, r, mx);
        return query(o << 1, l, (l + r) >> 1, mx) + tr[o].ans - tr[o << 1].ans;
    }

    void update(int o, int l, int r, int p, f64 v) {
        if (l == p && r == p) {
            tr[o].ans = 1, tr[o].mx = v;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) update(o << 1, l, mid, p, v);
        else update(o << 1 | 1, mid + 1, r, p, v);
        tr[o].mx = std::max(tr[o << 1].mx, tr[o << 1 | 1].mx);
        tr[o].ans = tr[o << 1].ans + query(o << 1 | 1, mid + 1, r, tr[o << 1].mx);
    }
} seg;


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        std::cin >> l >> r;
        seg.update(1, 1, n, l, (f64) r / l);
        std::cout << seg.tr[1].ans << "\n";
    }
    return 0;
}
