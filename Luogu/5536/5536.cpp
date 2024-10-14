#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, k;
int len, x, y, ans;
int dep[N], fa[N], mxd[N], dpl[N];

std::vector<int> G[N << 1];

void dfs1(int u, int pa) {
    if (len < dep[u]) { len = dep[u]; y = u; }
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v != pa) {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs1(v, u);
        }
    }
}

void dfs2(int u, int pa) {
    mxd[u] = dep[u];
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v != pa) {
            dep[v] = dep[u] + 1;
            fa[v] = u;
            dfs2(v, u);
            mxd[u] = std::max(mxd[u], mxd[v]);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    x = 1, y = 0, len = 0;
    dfs1(x, -1);

    len = 0;
    memset(fa, 0, sizeof(fa));
    memset(dep, 0, sizeof(dep));
    dfs1(y, -1);

    int pos = y;
    for (int i = 1; i <= ((dep[y] + 1) >> 1); i++, pos = fa[pos]);

    memset(fa, 0, sizeof(fa));
    memset(dep, 0, sizeof(dep));
    dfs2(pos, -1);
    for (int i = 1; i <= n; i++)
        dpl[i] = mxd[i] - dep[i];
    std::sort(dpl + 1, dpl + n + 1, std::greater<int>());
    for (int i = k + 1; i <= n; i++)
        ans = std::max(ans, dpl[i] + 1);
    std::cout << ans << "\n";
    return 0;
}
