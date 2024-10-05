#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int inf = 0x3f3f3f3f;

int n, m, w;
int a[N], nxt[N];
std::set<int> st[N];

struct SegTree {
    int tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void pushup(int o) { tr[o] = std::min(tr[o << 1], tr[o << 1 | 1]); }

    void build(int o, int l, int r) {
        if (l == r) { tr[o] = nxt[l]; return; }
        int mid = (l + r) >> 1;
        build(o << 1, l, mid);
        build(o << 1 | 1, mid + 1, r);
        pushup(o);
    }

    void update(int o, int l,int r, int p) {
        if (l == r) { tr[o] = nxt[p]; return; }
        int mid = (l + r) >> 1;
        if (p <= mid)
            update(o << 1, l, mid, p);
        else
            update(o << 1 | 1, mid + 1, r, p);
        pushup(o);
    }

    int query(int o, int l, int r, int p) {
        if (p <= l) return tr[o];
        int mid = (l + r) >> 1, ret = inf;
        if (p <= mid)
            ret = std::min(ret, query(o << 1, l, mid, p));
        ret = std::min(ret, query(o << 1 | 1, mid + 1, r, p));
        return ret;
    }
} seg;

int main() {
    scanf("%d %d %d", &n, &m, &w);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        st[std::min(a[i], w - a[i])].insert(i);
    }
    for (int i = 0; i <= (w >> 1); i++)
        st[i].insert(n + 1);
    for (int i = 1; i <= n; i++) {
        int u = std::min(a[i], w - a[i]);
        auto it = st[u].upper_bound(i);
        nxt[i] = (a[*it] + a[i] == w) ? (*it) : (n + 1);
    }
    seg.build(1, 1, n);

    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        int opt, x, y;
        scanf("%d %d %d", &opt, &x, &y);
        if (opt == 1) {
            int pa = std::min(a[x], w - a[x]);
            int py = std::min(y, w - y);
            st[pa].erase(x);
            auto it = st[pa].lower_bound(x);
            if (it != st[pa].begin()) {
                int j = *(it--);
                nxt[*it] = (a[j] + a[*it] == w) ? j : n + 1;
                seg.update(1, 1, n, *it);
            }
            a[x] = y;
            st[py].insert(x);
            it = st[py].upper_bound(x);
            nxt[x] = (a[*it] + a[x] == w) ? *it : n + 1;
            seg.update(1, 1, n, x);
            it = st[py].lower_bound(x);
            if (it != st[py].begin()) {
                int j = *(it--);
                nxt[*it] = (a[j] + a[*it] == w) ? j : n + 1;
                seg.update(1, 1, n, *it);
            }
        } else {
            x ^= cnt, y ^= cnt;
            bool flg = (seg.query(1, 1, n, x) <= y);
            cnt += flg;
            printf("%s\n", (flg ? "Yes" : "No"));
        }
    }
    return 0;
}
