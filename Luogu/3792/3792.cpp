#include <bits/stdc++.h>

#define int long long

constexpr int N = 5e5 + 7;
constexpr int P = 120605291;
constexpr int inf = 1e18;

int n, m;
int rmx, rmn, rsum, rsum2, rsum3;
int a[N];

struct node {
    int mx, mn, sum, sum2, sum3;
};

struct SegTree {
    node tr[N << 2];

    void pushup(int o) {
        tr[o].sum = tr[o << 1].sum + tr[o << 1 | 1].sum;
        tr[o].sum2 = (tr[o << 1].sum2 + tr[o << 1 | 1].sum2) % P;
        tr[o].sum3 = (tr[o << 1].sum3 + tr[o << 1 | 1].sum3) % P;
        tr[o].mn = std::min(tr[o << 1].mn, tr[o << 1 | 1].mn);
        tr[o].mx = std::max(tr[o << 1].mx, tr[o << 1 | 1].mx);
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o].mn = tr[o].mx = tr[o].sum = a[l];
            tr[o].sum2 = (a[l] * a[l]) % P;
            tr[o].sum3 = (tr[o].sum2 * a[l]) % P;
            return;
        }
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        pushup(o);
    }

    void update(int o, int l, int r, int p, int v) {
        if (l == r) {
            tr[o].mn = tr[o].mx = tr[o].sum = v;
            tr[o].sum2 = (v * v) % P;
            tr[o].sum3 = (tr[o].sum2 * v) % P;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) update(o << 1, l, mid, p, v);
        else update(o << 1 | 1, mid + 1, r, p, v);
        pushup(o);
    }

    void query(int o, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            rmn = std::min(rmn, tr[o].mn);
            rmx = std::max(rmx, tr[o].mx);
            rsum += tr[o].sum;
            (rsum2 += tr[o].sum2) %= P;
            (rsum3 += tr[o].sum3) %= P;
            return;
        }
        int mid = (l + r) >> 1;
        if (l <= mid)
            query(o << 1, l, mid, ql, qr);
        if (r > mid)
            query(o << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

int queryRsum2(int x) {
    return (x * (x + 1)) % P * (2 * x + 1) % P;
}

int queryRsum3(int x) {
    return (x * (x + 1)) % P * x % P * (x + 1) % P;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    seg.build(1, 1, n);
    while (m--) {
        int op, l, r, x;
        std::cin >> op;
        if (op == 1) {
            std::cin >> l >> x;
            seg.update(1, 1, n, l, x);
        } else {
            std::cin >> l >> r;
            rmn = inf, rmx = -inf;
            rsum = rsum2 = rsum3 = 0;
            seg.query(1, 1, n, l, r);
            if (rmx - rmn != r - l)
                std::cout << "yuanxing\n";
            else if (rsum != (rmx + rmn) * (rmx - rmn + 1) >> 1)
                std::cout << "yuanxing\n";
            else if (rsum2 * 6 % P != ((queryRsum2(rmx) - queryRsum2(rmn - 1)) % P + P) % P)
                std::cout << "yuanxing\n";
            else if (rsum3 * 4 % P != ((queryRsum3(rmx) - queryRsum3(rmn - 1)) % P + P) % P)
                std::cout << "yuanxing\n";
            else
                std::cout << "damushen\n";
        }
    }
    return 0;
}
