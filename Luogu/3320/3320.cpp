#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, dfc;
int dfn[N], idx[N], dep[N], fa[N][20];
i64 ans, dis[N];
bool vis[N];
std::set<int> st;
std::set<int>::iterator it;

struct edge {
    int to, val;
};
std::vector<edge> G[N << 1];

void dfs(int u, int pa) {
    dfn[u] = ++dfc;
    idx[dfc] = u;
    dep[u] = dep[fa[u][0] = pa] + 1;
    for (int j = 1; (1 << j) < dep[u]; j++)
        fa[u][j] = fa[fa[u][j - 1]][j - 1];
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i].to, w = G[u][i].val;
        if (v != pa) {
            dis[v] = dis[u] + w;
            dfs(v, u);
        }
    }
}

int lca(int x, int y) {
    if (dep[x] < dep[y])
        std::swap(x, y);
    for (int j = 0, d = dep[x] - dep[y]; d; j++, d >>= 1)
        if (d & 1)
            x = fa[x][j];
    if (x == y)
        return x;
    for (int j = 16; ~j; j--)
        if (fa[x][j] != fa[y][j])
            { x = fa[x][j]; y = fa[y][j]; }
    return fa[x][0];
}

i64 dist(int x, int y) { return dis[x] + dis[y] - 2 * dis[lca(x, y)]; }

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x, y, z;
        std::cin >> x >> y >> z;
        G[x].push_back({y, z});
        G[y].push_back({x, z});
    }
    dfs(1, 0);
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        std::cin >> x;
        x = dfn[x];
        if (!vis[idx[x]])
            st.insert(x);
        y = idx[(it = st.lower_bound(x)) == st.begin() ? *(--st.end()) : *(--it)];
        z = idx[(it = st.upper_bound(x)) == st.end() ? *st.begin() : *it];
        if (vis[idx[x]]) st.erase(x);
        x = idx[x];
        i64 d = dist(x, y) + dist(x, z) - dist(y, z);
        if (!vis[x]) { vis[x] = 1; ans += d; }
        else { vis[x] = 0; ans -= d; }
        std::cout << ans << "\n";
    }
    return 0;
}
