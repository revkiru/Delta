#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int R = 0x3f3f3f3f;

int n, e;
int a[N];

void cmax(int &a, int b) { if (a < b) a = b; }

struct node {
    bool vis;
    int ans, mxans;
    int sum, val, mxsum, mxval;
};

struct SegTree {
    node tr[N << 2];

    #define ls(o) o << 1
    #define rs(o) o << 1 | 1

    void pushup(int o) {
        tr[o].ans = std::max(tr[ls(o)].ans, tr[rs(o)].ans);
        tr[o].mxans = std::max(tr[ls(o)].mxans, tr[rs(o)].mxans);
    }

    void tagSum(int o, int k, int mxk) {
        if (tr[o].vis) {
            cmax(tr[o].mxval, tr[o].val + mxk);
            cmax(tr[o].mxans, tr[o].ans + mxk);
            tr[o].ans += k;
            tr[o].val += k;
        } else {
            cmax(tr[o].mxsum, tr[o].sum + mxk);
            cmax(tr[o].mxans, tr[o].ans + mxk);
            tr[o].ans += k;
            tr[o].sum += k;
        }
    }

    void tagVal(int o, int k, int mxk) {
        if (tr[o].vis) {
            cmax(tr[o].mxval, mxk);
            cmax(tr[o].mxans, mxk);
        } else {
            tr[o].vis = 1;
            tr[o].mxval = mxk;
            cmax(tr[o].mxans, mxk);
        }
        tr[o].ans = tr[o].val = k;
    }

    void pushdown(int o) {
        tagSum(ls(o), tr[o].sum, tr[o].mxsum);
        tagSum(rs(o), tr[o].sum, tr[o].mxsum);
        tr[o].sum = tr[o].mxsum = 0;
        if (tr[o].vis) {
            tagVal(ls(o), tr[o].val, tr[o].mxval);
            tagVal(rs(o), tr[o].val, tr[o].mxval);
            tr[o].vis = 0;
            tr[o].val = tr[o].mxval = 0;
        }
    }

    #undef ls(o)
    #undef rs(o)

    void build(int o, int l, int r) {
        if (l == r) {
            std::cin >> tr[o].ans;
            tr[o].mxans = tr[o].ans;
            return;
        }
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        pushup(o);
    }

    int bigQuery(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].ans;
        pushdown(o);
        int mid = (l + r) >> 1, ret = -R;
        if (ql <= mid) ret = bigQuery(o << 1, l, mid, ql, qr);
        if (mid < qr) cmax(ret, bigQuery(o << 1 | 1, mid + 1, r, ql, qr));
        return ret;
    }

    int hisQuery(int o, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tr[o].mxans;
        pushdown(o);
        int mid = (l + r) >> 1, ret = -R;
        if (ql <= mid) ret = hisQuery(o << 1, l, mid, ql, qr);
        if (mid < qr) cmax(ret, hisQuery(o << 1 | 1, mid + 1, r, ql, qr));
        return ret;
    }

    void add(int o, int l, int r, int ql, int qr, int k) {
        if (ql <= l && r <= qr) {
            tagSum(o, k, k);
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (ql <= mid) add(o << 1, l, mid, ql, qr, k);
        if (mid < qr) add(o << 1 | 1, mid + 1, r, ql, qr, k);
        pushup(o);
    }

    void modify(int o, int l, int r, int ql, int qr, int k) {
        if (ql <= l && r <= qr) {
            tagVal(o, k, k);
            return;
        }
        pushdown(o);
        int mid = (l + r) >> 1;
        if (ql <= mid) modify(o << 1, l, mid, ql, qr, k);
        if (mid < qr) modify(o << 1 | 1, mid + 1, r, ql, qr, k);
        pushup(o);
    }
} seg;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    seg.build(1, 1, n);
    std::cin >> e;
    while (e--) {
        char opt;
        int x, y, z;
        std::cin >> opt >> x >> y;
        if (opt == 'Q')
            std::cout << seg.bigQuery(1, 1, n, x, y) << "\n";
        if (opt == 'A')
            std::cout << seg.hisQuery(1, 1, n, x, y) << "\n";
        if (opt == 'P') {
            std::cin >> z;
            seg.add(1, 1, n, x, y, z);
        }
        if (opt == 'C') {
            std::cin >> z;
            seg.modify(1, 1, n, x, y, z);
        }
    }
    return 0;
}
