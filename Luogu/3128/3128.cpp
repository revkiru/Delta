#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, k, t0t, ans;
int dep[N], fa[N], siz[N], son[N];
int rnk[N], dfn[N], top[N], d[N], val[N];
std::vector<int> G[N << 1];

void dfs1(int u) {
    son[u] = -1;
    siz[u] = 1;
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (!dep[v]) {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v);
            siz[u] += siz[v];
            if (son[u] == -1 || (siz[v] > siz[son[u]]))
                son[u] = v;
        }
    }
}

void dfs2(int u, int pa) {
    top[u] = pa;
    dfn[u] = ++t0t;
    rnk[t0t] = u;
    if (son[u] == -1)   
        return;
    dfs2(son[u], pa);
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v != son[u] && v != fa[u])
            dfs2(v, v);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]])
            u = fa[top[u]];
        else
            v = fa[top[v]];
    }
    return dep[u] > dep[v] ? v : u;
}

void solve(int u, int v) {
    d[u]++, d[v]++;
    int _l = lca(u, v);
    d[_l]--, d[fa[_l]]--;
}

void dfs(int u) {
    val[u] = d[u];
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == fa[u]) continue;
        dfs(v);
        val[u] += val[v];
    }
    ans = std::max(ans, val[u]);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dep[1] = 1;
    dfs1(1);
    dfs2(1, 1);
    for (int i = 1; i <= k; i++) {
        int a, b;
        std::cin >> a >> b;
        solve(a, b);
    }
    dfs(1);
    std::cout << ans << "\n";
    return 0;
}
