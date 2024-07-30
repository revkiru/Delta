#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;
constexpr int P = 1e9 + 7;

int n, m;
int pcnt, ecnt;
int vis[N];
std::vector<int> G[N << 1];

void dfs(int u) {
    vis[u] = 1;
    pcnt++;
    for (size_t i = 0; i < G[u].size(); i++, ecnt++) {
        if (!vis[G[u][i]])
            dfs(G[u][i]);
    }
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int ans = 1;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            pcnt = ecnt = 0;
            dfs(i);
            if (pcnt > ecnt / 2) ans = (ans * pcnt) % P;
            else if (pcnt == ecnt / 2) ans = (ans * 2) % P;
            else { ans = 0; break; }
        }
    }

    std::cout << ans << "\n";
    return 0;
}
