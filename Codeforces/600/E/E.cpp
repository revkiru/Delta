#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int R = 1e5;

int n, t0t;
int clr[N], rt[N], ans[N];

struct node {
    int l, r, sum, val, ans;
};

std::vector<int> G[N << 1];

struct SegTree {
    node tr[N << 2];

    void pushup(int o) {
        if (tr[tr[o].l].sum > tr[tr[o].r].sum) {
            tr[o].sum = tr[tr[o].l].sum;
            tr[o].val = tr[tr[o].l].val;
            tr[o].ans = tr[tr[o].l].ans;
        }
        if (tr[tr[o].r].sum > tr[tr[o].l].sum) {
            tr[o].sum = tr[tr[o].r].sum;
            tr[o].val = tr[tr[o].r].val;
            tr[o].ans = tr[tr[o].r].ans;
        }
        if (tr[tr[o].l].sum == tr[tr[o].r].sum) {
            tr[o].sum = tr[tr[o].l].sum;
            tr[o].val = tr[tr[o].l].val;
            tr[o].ans = tr[tr[o].l].ans + tr[tr[o].r].ans;
        }
    }

    void update(int &o, int l, int r, int p, int v) {
        if (!o) o = ++t0t;
        if (l == r) {
            tr[o].val = l;
            tr[o].sum += v;
            tr[o].ans = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            update(tr[o].l, l, mid, p, v);
        else
            update(tr[o].r, mid + 1, r, p, v);
        pushup(o);
    }

    int merge(int a, int b, int l, int r) {
        if (!a) return b;
        if (!b) return a;
        if (l == r) {
            tr[a].val = l;
            tr[a].sum += tr[b].sum;
            tr[a].ans = l;
            return a;
        }
        int mid = (l + r) >> 1;
        tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
        tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
        pushup(a);
        return a;
    }
} seg;

void dfs(int u, int fa) {
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == fa) continue;
        dfs(v, u);
        seg.merge(rt[u], rt[v], 1, R);
    }
    seg.update(rt[u], 1, R, clr[u], 1);
    ans[u] = seg.tr[rt[u]].ans;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> clr[i];
        rt[i] = i;
        t0t++;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        std::cout << ans[i] << " ";
    return 0;
}
