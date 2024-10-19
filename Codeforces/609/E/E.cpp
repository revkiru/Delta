#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, m, ans, tot = 1;
int a[N], f[N];
int dep[N], fa[N], siz[N], son[N], top[N];
int seg[N], rev[N];

struct edge {
    int a, b, c;
} E[N], d[N];

std::vector<int> g[N], e[N];

struct node {
    int l, r, mx;
} tr[N << 2];

int find(int x) { return (f[x] == x ? f[x] : f[x] = find(f[x])); }

bool cmp(const edge &a, const edge &b) { return a.c < b.c; }

void dfs1(int u, int pa) {
    dep[u] = dep[pa] + 1;
    fa[u] = pa;
    siz[u] = 1;
    for (int i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v != pa) {
            a[v] = e[u][i];
            dfs1(v, u);
            siz[u] += siz[v];
            if (siz[v] > siz[son[u]])
                son[u] = v;
        }
    }
}

void dfs2(int u, int pa) {
    if (son[u]) {
        top[son[u]] = top[u];
        seg[son[u]] = ++tot;
        rev[tot] = son[u];
        dfs2(son[u], u);
        for (int i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v != pa && v != son[u]) {
                top[v] = v;
                seg[v] = ++tot;
                rev[tot] = v;
                dfs2(v, u);
            }
        }
    }
}

#define ls(o) (o << 1)
#define rs(o) (o << 1 | 1)

void pushup(int o) { tr[o].mx = std::max(tr[ls(o)].mx, tr[rs(o)].mx); }

void build(int o, int l, int r) {
    tr[o].l = l, tr[o].r = r;
    if (l == r) { tr[o].mx = a[rev[l]]; return; }
    int mid = (tr[o].l + tr[o].r) >> 1;
    build(ls(o), l, mid);
    build(rs(o), mid + 1, r);
    pushup(o);
}

int query(int o, int ql, int qr) {
    if (ql > qr) return 0;
    if (ql <= tr[o].l && tr[o].r <= qr) return tr[o].mx;
    int ans = 0;
    int mid = (tr[o].l + tr[o].r) >> 1;
    if (ql <= mid) ans = std::max(ans, query(ls(o), ql, qr));
    if (qr > mid) ans = std::max(ans, query(rs(o), ql, qr));
    return ans;
}

int rangeQuery(int x, int y) {
    int ans = 0;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]])
            std::swap(x, y);
        ans = std::max(ans, query(1, seg[top[x]], seg[x]));
        x = fa[top[x]];
        if (x == 0) x = 1;
    }
    if (dep[x] > dep[y]) std::swap(x, y);
    ans = std::max(ans, query(1, seg[son[x]], seg[y]));
    return ans;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        std::cin >> E[i].a >> E[i].b >> E[i].c;
        d[i] = E[i];
    }
    for (int i = 1; i <= n; i++)
        f[i] = i;
    std::sort(E + 1, E + m + 1, cmp);
    // std::cout << "---\n";
    // for (int i = 1; i <= m; i++) {
    //     std::cout << E[i].a << " " << E[i].b << " " << E[i].c << "\n";
    // }
    // std::cout << "---\n";
    for (int i = 1; i <= m; i++) {
        int fx = find(E[i].a), fy = find(E[i].b);
        // std::cout << f[fx] << "---" << f[fy] << "\n";
        if (fx == fy) continue;
        f[fx] = fy;
        g[E[i].a].push_back(E[i].b);
        e[E[i].a].push_back(E[i].c);
        g[E[i].b].push_back(E[i].a);
        e[E[i].b].push_back(E[i].c);
        ans += E[i].c;
    }
    dfs1(1, 0);
    // for (int i = 1; i <= n; i++)
    //     std::cout << dep[i] << " " << fa[i] << " " << siz[i] << "\n";
    top[1] = seg[1] = rev[1] = 1;
    dfs2(1, 0);
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
        std::cout << (ans + d[i].c - rangeQuery(d[i].a, d[i].b)) << "\n";
    return 0;
}
