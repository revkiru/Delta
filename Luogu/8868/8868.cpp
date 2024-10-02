#include <bits/stdc++.h>

constexpr int N = 3e5 + 5;

#define int unsigned long long

struct info {
    int s, sx, sy, sxy;
    info() { s = sx = sy = sxy = 0; }
    info(int _s, int _sx, int _sy, int _sxy) { s = _s, sx = _sx, sy = _sy, sxy = _sxy; }
    void clear() { s = sx = sy = sxy = 0; }
} fi[N << 2];

struct tag {
    int cx, cy, ax, ay, axy, c;
    tag() { cx = cy = ax = ay = axy = c = 0; }
    tag(int _cx, int _cy, int _ax, int _ay, int _axy, int _c) { cx = _cx, cy = _cy, ax = _ax, ay = _ay, axy = _axy, c = _c; }
    void clear() { cx = cy = ax = ay = axy = c = 0; }
    bool emity() { return !(cx || cy || ax || ay || axy || c); }
} tg[N << 2];

info merge(info x, info y) { return info(x.s + y.s, x.sx + y.sx, x.sy + y.sy, x.sxy + y.sxy); }

tag merge(tag x, tag y) {
    if (y.cx && y.cy)
        y.c += x.axy * y.cx * y.cy + x.ax * y.cx + x.ay * y.cy + x.c;
    else if (y.cx) {
        y.ay += x.axy * y.cx + x.ay;
        y.c += x.c + x.ax * y.cx;
    } else if (y.cy) {
        y.ax += x.axy * y.cy + x.ax;
        y.c += x.c + x.ay * y.cy;
    } else {
        y.axy += x.axy;
        y.ax += x.ax;
        y.ay += x.ay;
        y.c += x.c;
    }
    if (x.cx)
        y.cx = x.cx;
    if (x.cy)
        y.cy = x.cy;
    return y;
}

info merge(info x, tag y, int len) {
    x.s += y.axy * x.sxy + y.ax * x.sx + y.ay * x.sy + y.c * len;
    if (y.cx && y.cy) {
        x.sxy = len * y.cx * y.cy;
        x.sx = len * y.cx;
        x.sy = len * y.cy;
    } else if (y.cx) {
        x.sxy = x.sy * y.cx;
        x.sx = len * y.cx;
    } else if (y.cy) {
        x.sxy = x.sx * y.cy;
        x.sy = len * y.cy;
    }
    return x;
}

struct SegTree {
    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void pushup(int o) { fi[o] = merge(fi[ls(o)], fi[rs(o)]); }

    void pushdown(int o, int l, int r) {
        if (!tg[o].emity()) {
            int mid = (l + r) >> 1;
            int l1 = (mid - l + 1), l2 = (r - mid);
            tg[ls(o)] = merge(tg[o], tg[ls(o)]), tg[rs(o)] = merge(tg[o], tg[rs(o)]);
            fi[ls(o)] = merge(fi[ls(o)], tg[o], l1), fi[rs(o)] = merge(fi[rs(o)], tg[o], l2);
            tg[o].clear();
            return;
        }
    }

    void update(int o, int l, int r, int ql, int qr, tag t) {
        if (ql <= l && r <= qr) {
            tg[o] = merge(t, tg[o]);
            fi[o] = merge(fi[o], t, r - l + 1);
            return;
        }
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(ls(o), l, mid, ql, qr, t);
        if (qr > mid)
            update(rs(o), mid + 1, r, ql, qr, t);
        pushup(o);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return fi[o].s;
        }
        pushdown(o, l, r);
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(ls(o), l, mid, ql, qr);
        if (qr > mid)
            res += query(rs(o), mid + 1, r, ql, qr);
        return res;
    }
} seg;

struct node {
    int l, id;
    node() { l = id = 0; }
    node(int _l, int _id) { l = _l, id = _id; }
} qs[N];

int t, n, q;
int it[N], sz[N];
int a[N], b[N], stc[N][2], tp[2];
std::vector<node> vec[N];

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("match.in", "r", stdin);
    // freopen("match.out", "w", stdout);

    std::cin >> t >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
        std::cin >> b[i];
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        std::cin >> qs[i].l >> qs[i].id;
        sz[qs[i].id]++;
    }
    for (int i = 1; i <= n; i++)
        vec[i].reserve(sz[i]);
    for (int i = 1; i <= q; i++)
        vec[qs[i].id].push_back(node(qs[i].l, i));
    for (int i = 1; i <= n; i++) {
        while (tp[0] > 0 && a[stc[tp[0]][0]] < a[i])
            tp[0]--;
        seg.update(1, 1, n, stc[tp[0]][0] + 1, i, tag(a[i], 0, 0, 0, 0, 0));
        stc[++tp[0]][0] = i;
        while (tp[1] > 0 && b[stc[tp[1]][1]] < b[i])
            tp[1]--;
        seg.update(1, 1, n, stc[tp[1]][1] + 1, i, tag(0, b[i], 0, 0, 0, 0));
        stc[++tp[1]][1] = i;
        seg.update(1, 1, n, 1, i, tag(0, 0, 0, 0, 1, 0));
        int Sz = (int) vec[i].size();
        for (int j = 0; j < Sz; j++)
            it[vec[i][j].id] = seg.query(1, 1, n, vec[i][j].l, i);
    }
    for (int i = 1; i <= q; i++)
        std::cout << it[i] << "\n";
    return 0;
}
