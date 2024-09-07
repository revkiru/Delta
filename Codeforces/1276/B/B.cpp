#include <bits/stdc++.h>

using i64 = long long;

constexpr int M = 5e5 + 7;

int n, m, a, b;
int t0t;
i64 s1, s2;
bool vis[M << 1];

std::vector<int> G[M << 1];

int e[M << 1], h[M << 1], nxt[M << 1];
void addEdge(int u, int v) {
    ++t0t;
    e[t0t] = v;
    nxt[t0t] = h[u];
    h[u] = t0t;
    ++t0t;
    e[t0t] = u;
    nxt[t0t] = h[v];
    h[v] = t0t;
}

void MyClear() {
    t0t = s1 = s2 = 0;
    for (int i = 0; i <= n; i++) {
        h[i] = 0;
        vis[i] = 0;
    }
}

void bfs(int s) {
    std::queue<int> q;
    q.push(s);
    vis[s] = vis[b] = 1;   
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int p = h[u]; p; p = nxt[p]) {
            int v = e[p];
            if (!vis[v]) { vis[v] = 1; q.push(v); }
        }
    }
}

void dfs(int u) {
    for (int p = h[u]; p; p = nxt[p]) {
        int v = e[p];
        if (!vis[v]) { vis[v] = 1; dfs(v); }
    }
}

void solve() {
    std::cin >> n >> m >> a >> b;
    MyClear();
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        addEdge(u, v);
    }
    bfs(a);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            ++s1;
    memset(vis, 0, sizeof(vis));
    vis[a] = 1;
    dfs(b);
    for (int i = 1; i <= n; i++)
        if (!vis[i])
            ++s2;
    std::cout << 1ll * s1 * s2 << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
