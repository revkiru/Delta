#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n, Q, tot;
int l[N], r[N];
i64 d;
i64 a[N], b[N], s[N];
i64 ans[N], _s[N], ind[N];
bool flg[N];

std::vector<std::pair<int, int>> e[N];

struct node {
    i64 val, lzy;
};

struct SegTree {
    node tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void maketag(int o, int l, int r, i64 x) {
        tr[o].val += 1ll * (r - l + 1) * x;
        tr[o].lzy += x;
    }

    void pushdown(int o, int l, int r) {
        if (tr[o].lzy) {
            int mid = (l + r) >> 1;
            maketag(o << 1, l, mid, tr[o].lzy);
            maketag(o << 1 | 1, mid + 1, r, tr[o].lzy);
            tr[o].lzy = 0;
        }
    }

    void pushup(int o) { tr[o].val = tr[o << 1].val + tr[o << 1 | 1].val; }

    void update(int o, int l, int r, int ql, int qr, i64 v) {
        if (ql <= l && r <= qr) { maketag(o, l, r, v); return; }
        int mid = (l + r) >> 1;
        pushdown(o, l, r);
        if (ql <= mid) update(o << 1, l, mid, ql, qr, v);
        if (qr > mid) update(o << 1 | 1, mid + 1, r, ql, qr, v);
        pushup(o);
    }

    i64 query1(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) { return tr[o].val; }
        int mid = (l + r) >> 1;
        pushdown(o, l, r);
        i64 ret = 0;
        if (ql <= mid)
            ret += query1(o << 1, l, mid, ql, qr);
        if (qr > mid)
            ret += query1(o << 1 | 1, mid + 1, r, ql, qr);
        return ret;
    }

    i64 query2(int o, int l, int r, int v) {
        if (l == r) { return tr[o].val; }
        int mid = (l + r) >> 1;
        pushdown(o, l, r);
        if (v <= mid)
            return query2(o << 1, l, mid, v);
        return query2(o << 1 | 1, mid + 1, r, v);
    }
} seg;

int main() {
    scanf("%d %lld", &n, &d);
    for (int i = 1; i <= n; i++)
        scanf("%lld", &a[i]);
    scanf("%d", &Q);
    for (int i = 1; i <= Q; i++) {
        int l, r;
        scanf("%d %d", &l, &r);
        e[r].push_back({l, i});
    }
    for (int i = 1; i <= n; i++) {
        b[i] = a[i] / d;
        a[i] %= d;
        s[i] = s[i - 1];
        _s[i] = _s[i - 1];
        if (a[i] < a[i - 1]) { ++s[i]; flg[i] = 1; }
        _s[i] += b[i];
    }
    for (int i = 1; i <= n; i++) {
        i64 x = b[i];
        while (tot && ind[tot] + flg[r[tot] + 1] >= x) {
            i64 ls = ind[tot] + flg[r[tot] + 1] - x;
            seg.update(1, 1, n, l[tot], r[tot], -ls);
            x -= s[r[tot] + 1] - s[l[tot]];
            tot--;
        }
        ind[++tot] = b[i];
        l[tot] = r[tot - 1] + 1;
        r[tot] = i;
        seg.update(1, 1, n, i, i, b[i]);
        for (auto j : e[i]) {
            if (seg.query2(1, 1, n, j.first) < 0)
                ans[j.second] = -1;
            else
                ans[j.second] = _s[i] - _s[j.first - 1] - seg.query1(1, 1, n, j.first, i);
        }
    }
    for (int i = 1; i <= Q; i++)
        printf("%lld\n", ans[i]);
    return 0;
}
