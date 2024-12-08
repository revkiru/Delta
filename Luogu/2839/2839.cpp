#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e4 + 7;

int n, m, len;
int a[N], b[N], q[4];
std::vector<int> v[N];

struct node {
    int ls, rs, lmx, rmx;
    i64 sum;
};

struct PersistentSegTree {
    int rcnt, rt[N];
    node tr[N << 5];

    #define ls(o) (tr[o].ls)
    #define rs(o) (tr[o].rs)

    void pushup(int o) {
        tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum;
        tr[o].lmx = std::max((i64) tr[ls(o)].lmx, tr[ls(o)].sum + tr[rs(o)].lmx);
        tr[o].rmx = std::max((i64) tr[rs(o)].rmx, tr[ls(o)].rmx + tr[rs(o)].sum);
    }

    void build(int &o, int l, int r) {
        if (!o) o = ++rcnt;
        if (l == r) {
            tr[o].sum = tr[o].lmx = tr[o].rmx = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        pushup(o);
    }

    void update(int ori, int &o, int l, int r, int x) {
        o = ++rcnt;
        tr[o] = tr[ori];
        if (l == r) {
            tr[o].sum = tr[o].lmx = tr[o].rmx = -1;
            return;
        }
        int mid = (l + r) >> 1;
        if (x <= mid)
            update(ls(ori), ls(o), l, mid, x);
        else
            update(rs(ori), rs(o), mid + 1, r, x);
        pushup(o);
    }

    i64 querySum(int o, int l, int r, int ql, int qr) {
        if (qr < ql) return 0;
        if (l == ql && r == qr) return tr[o].sum;
        int mid = (l + r) >> 1;
        if (qr <= mid) return querySum(ls(o), l, mid, ql, qr);
        else if (ql > mid) return querySum(rs(o), mid + 1, r, ql, qr);
        else return querySum(ls(o), l, mid, ql, mid) + querySum(rs(o), mid + 1, r, mid + 1, qr);
    }

    i64 queryL(int o, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) return tr[o].lmx;
        int mid = (l + r) >> 1;
        if (qr <= mid) return queryL(ls(o), l, mid, ql, qr);
        else if (ql > mid) return queryL(rs(o), mid + 1, r, ql, qr);
        else {
            int ret1 = queryL(ls(o), l, mid, ql, mid);
            int ret2 = querySum(ls(o), l, mid, ql, mid) + queryL(rs(o), mid + 1, r, mid + 1, qr);
            return std::max(ret1, ret2);
        }
    }

    int queryR(int o, int l, int r, int ql, int qr) {
        if (l == ql && r == qr) return tr[o].rmx;
        int mid = (l + r) >> 1;
        if (qr <= mid) return queryR(ls(o), l, mid, ql, qr);
        else if (ql > mid) return queryR(rs(o), mid + 1, r, ql, qr);
        else {
            int ret1 = queryR(rs(o), mid + 1, r, mid + 1, qr);
            int ret2 = querySum(rs(o), mid + 1, r, mid + 1, qr) + queryR(ls(o), l, mid, ql, mid);
            return std::max(ret1, ret2);
        }
    }
} pSeg;

bool check(int x) {
    int ret1 = pSeg.querySum(pSeg.rt[x], 1, n, q[1] + 1, q[2] - 1);
    int ret2 = pSeg.queryR(pSeg.rt[x], 1, n, q[0], q[1]);
    int ret3 = pSeg.queryL(pSeg.rt[x], 1, n, q[2], q[3]);
    return ret1 + ret2 + ret3 >= 0;
}

int solve() {
    int l = 1, r = len;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid))
            l = mid;
        else
            r = mid - 1;
    }
    return l;
}

int main() {
    scanf("%d", &n);
    pSeg.build(pSeg.rt[0], 1, n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    len = std::unique(b + 1, b + n + 1) - b - 1;
    for (int i = 1; i <= n; i++) {
        a[i] = std::lower_bound(b + 1, b + len + 1, a[i]) - b;
        v[a[i]].push_back(i);
    }
    for (int i = 1; i <= len; i++) {
        pSeg.rt[i] = pSeg.rt[i - 1];
        for (size_t j = 0; j < v[i - 1].size(); j++)
            pSeg.update(pSeg.rt[i], pSeg.rt[i], 1, n, v[i - 1][j]);
    }

    scanf("%d", &m);
    for (int i = 1, ans = 0; i <= m; i++) {
        for (int j = 0; j < 4; j++)
            scanf("%d", &q[j]);
        for (int j = 0; j < 4; j++)
            q[j] = (q[j] + ans) % n + 1;
        std::sort(q, q + 4);
        ans = b[solve()];
        printf("%d\n", ans);
    }
    return 0;
}
