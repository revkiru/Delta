#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, m;
int a[N];

struct SegTree {
    struct node {
        int sum, cov;
    } tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void pushup(const int o) {
        tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum;
    }

    void pushdown(const int o) {
        if (tr[o].cov) {
            tr[ls(o)].cov = 1, tr[ls(o)].sum = 0;
            tr[rs(o)].cov = 1, tr[rs(o)].sum = 0;
            tr[o].cov = 0;
        }
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o].sum = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        pushup(o);
    }

    void update(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            tr[o].sum = 0, tr[o].cov = 1;
            return;
        }
        int mid = (l + r) >> 1;
        pushdown(o);
        if (ql <= mid) update(ls(o), l, mid, ql, qr);
        if (qr > mid) update(rs(o), mid + 1, r, ql, qr);
        pushup(o);
    }
} seg;

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++)
        a[i] = 1;
    seg.build(1, 1, n);
    for (int i = 1, a, b; i <= m; i++) {
        scanf("%d %d", &a, &b);
        seg.update(1, 1, n, a, b);
        printf("%d\n", seg.tr[1].sum);
    }
    return 0;
}
