#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e6 + 7;
constexpr int M = 5e5 + 7;
constexpr int inf = 1e9;

int n, m, rt, top;
int a[M], stc[M];

std::random_device rdv;
std::mt19937 myrand(rdv());

struct node {
    int val, siz, rd, sum, tag, mxl, mxr, mxs, ls, rs;
    bool rev, vis;
};

struct Treap {
    int tim;
    node tr[N];

    #define ls(o) (tr[o].ls)
    #define rs(o) (tr[o].rs)

    int newnode(int x) {
        int idx = top ? stc[top--] : ++tim;
        memset(tr + idx, 0, sizeof(node));
        tr[idx].val = tr[idx].sum = x; tr[idx].mxs = x; tr[idx].mxl = tr[idx].mxr = std::max(x, 0); tr[idx].siz = 1; tr[idx].rd = myrand();
        return idx;
    }

    void pushup(const int o) {
        if (!o) return;
        if (tr[o].vis) {
            tr[o].siz = tr[ls(o)].siz + tr[rs(o)].siz + 1;
            tr[o].sum = tr[o].tag * tr[o].siz;
            if (tr[o].tag > 0) {
                tr[o].mxl = tr[o].mxr = tr[o].mxs = tr[o].sum;
            } else {
                tr[o].mxs = tr[o].tag;
                tr[o].mxl = tr[o].mxr = 0;
            }
            // std::cout << tr[o].siz << " " << tr[o].sum << " " << tr[o].mxl << " " << tr[o].mxr << " " << tr[o].mxs << "...\n";
            return;
        }
        tr[o].siz = tr[ls(o)].siz + tr[rs(o)].siz + 1;
        tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum + tr[o].val;
        tr[o].mxl = std::max(tr[ls(o)].mxl, tr[ls(o)].sum + tr[o].val + tr[rs(o)].mxl);
        tr[o].mxr = std::max(tr[rs(o)].mxr, tr[rs(o)].sum + tr[o].val + tr[ls(o)].mxr);
        tr[o].mxs = std::max({tr[ls(o)].mxs, tr[rs(o)].mxs, tr[ls(o)].mxr + tr[o].val + tr[rs(o)].mxl});
        // std::cout << tr[o].siz << " " << tr[o].sum << " " << tr[o].mxl << " " << tr[o].mxr << " " << tr[o].mxs << "!!!\n";
        if (tr[o].rev) std::swap(tr[o].mxl, tr[o].mxr);
    }

    void pushdown(int o) {
        if (o) {
            if (tr[o].rev) {
                std::swap(ls(o), rs(o));
                tr[ls(o)].rev = !tr[ls(o)].rev;
                tr[rs(o)].rev = !tr[rs(o)].rev;
                std::swap(tr[ls(o)].mxl, tr[ls(o)].mxr);
                std::swap(tr[rs(o)].mxl, tr[rs(o)].mxr);
            }
            if (tr[o].vis) {
                tr[ls(o)].tag = tr[rs(o)].tag = tr[o].tag;
                tr[ls(o)].vis = tr[rs(o)].vis = 1;
                tr[o].val = tr[o].tag;
                pushup(ls(o));
                pushup(rs(o));
            }
        }
        tr[o].vis = tr[o].rev = 0;
    }

    void split(int o, int k, int &x, int &y) {
        if (!o) { x = y = 0; return; }
        pushdown(o);
        if (tr[ls(o)].siz < k) {
            x = o;
            split(rs(o), k - tr[ls(o)].siz - 1, rs(o), y);
            pushup(x);
        } else {
            y = o;
            split(ls(o), k, x, ls(o));
            pushup(y);
        }
    }

    int merge(int x, int y) {
        if (!x || !y) { pushup(x); pushup(y); return x + y; }
        pushdown(x);
        pushdown(y);
        if (tr[x].rd < tr[y].rd) {
            rs(x) = merge(rs(x), y);
            pushup(x);
            return x;
        } else {
            ls(y) = merge(x, ls(y));
            pushup(y);
            return y;
        }
    }

    int build(int l, int r) {
        if (l > r) return 0;
        if (l == r) return newnode(a[l]);
        int mid = (l + r) >> 1;
        int o = newnode(a[mid]);
        ls(o) = build(l, mid - 1);
        rs(o) = build(mid + 1, r);
        pushup(o);
        return o;
    }
} trp;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    
    trp.tr[0].mxs = -inf;
    rt = trp.build(1, n);
    for (int _t = 1, l, tot, c; _t <= m; _t++) {
        std::string s;
        std::cin >> s;
        if (s == "INSERT") {
            std::cin >> l >> tot;
            for (int i = 1; i <= tot; i++)
                std::cin >> a[i];
            int ql, qr;
            trp.split(rt, l, ql, qr);
            rt = trp.merge(ql, trp.merge(trp.build(1, tot), qr));
        }
        if (s == "DELETE") {
            std::cin >> l >> tot;
            int ql, qr, _q;
            trp.split(rt, l - 1, ql, qr);
            trp.split(qr, tot, _q, qr);
            stc[++top] = _q;
            rt = trp.merge(ql, qr);
        }
        if (s == "MAKE-SAME") {
            std::cin >> l >> tot >> c;
            int ql, qr, _q;
            trp.split(rt, l - 1, ql, qr);
            trp.split(qr, tot, _q, qr);
            trp.tr[_q].tag = c;
            trp.tr[_q].vis = 1;
            trp.pushup(_q);
            rt = trp.merge(ql, trp.merge(_q, qr));
        }
        if (s == "REVERSE") {
            std::cin >> l >> tot;
            int ql, qr, _q;
            trp.split(rt, l - 1, ql, qr);
            trp.split(qr, tot, _q, qr);
            trp.tr[_q].rev = !trp.tr[_q].rev;
            std::swap(trp.tr[_q].mxl, trp.tr[_q].mxr);
            rt = trp.merge(ql, trp.merge(_q, qr));
        }
        if (s == "GET-SUM") {
            std::cin >> l >> tot;
            int ql, qr, _q;
            trp.split(rt, l - 1, ql, qr);
            trp.split(qr, tot, _q, qr);
            std::cout << trp.tr[_q].sum << "\n";
            rt = trp.merge(ql, trp.merge(_q, qr));
        }
        if (s == "MAX-SUM") {
            std::cout << trp.tr[rt].mxs << "\n";
        }
    }
    return 0;
}
