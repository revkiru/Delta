#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, m, k;

struct undoProject {
    int pos, val;
};

std::stack<undoProject> undoSz, undoFa;

struct UnionFind {
    int fa[N << 1], siz[N << 1];

    void init() { std::iota(fa + 1, fa + (n << 1) + 1, 1); std::fill(siz + 1, siz + (n << 1) + 1, 1); }

    int find(int x) { if (fa[x] == x) return x; return find(fa[x]); }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y)
            return;
        if (siz[x] < siz[y])
            std::swap(x, y);
        undoSz.push({x, siz[x]});
        siz[x] += siz[y];
        undoFa.push({y, fa[y]});
        fa[y] = x;
    }

    void undo() {
        fa[undoFa.top().pos] = undoFa.top().val;
        undoFa.pop();
        siz[undoSz.top().pos] = undoSz.top().val;
        undoSz.pop();
    }
} uni;

std::vector<int> tr[N << 2];

void update(int o, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        tr[o].push_back(v);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(o << 1, l, mid, ql, qr, v);
    if (qr > mid)
        update(o << 1 | 1, mid + 1, r, ql, qr, v);
}

struct edge {
    int u, v;
} G[N << 1];

std::vector<bool> ret;

void solve(int i, int l, int r) {
    size_t level = undoFa.size();
    bool flg = 1;
    for (auto u : tr[i]) {
        int fu = uni.find(G[u].u);
        int fv = uni.find(G[u].v);
        if (fu == fv) {
            for (int k = l; k <= r; k++)
                ret.push_back(0);
            flg = 0;
            break;
        }
        uni.unite(G[u].u, G[u].v + n);
        uni.unite(G[u].v, G[u].u + n);
    }
    if (flg) {
        if (l == r)
            ret.push_back(1);
        else {
            int mid = (l + r) >> 1;
            solve(i << 1, l, mid);
            solve(i << 1 | 1, mid + 1, r);
        }
    }
    while (undoFa.size() > level)
        uni.undo();
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    uni.init();
    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d %d %d %d", &G[i].u, &G[i].v, &l, &r);
        update(1, 1, k, l + 1, r, i);
    }
    solve(1, 1, k);
    for (auto i : ret)
        printf("%s\n", (i ? "Yes" : "No"));
    return 0;
}
