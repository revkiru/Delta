#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = (307 << 1);

struct edge {
    int to, val;
};

int n, m, k;
int ret[N][2], dp[N][N][2];
std::vector<edge> G[N];

void dfs(int u, int fa) {
    dp[u][0][0] = dp[u][1][1] = 0;
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i].to, w = G[u][i].val;
        if (v == fa) continue;
        dfs(v, u);
        memcpy(ret, dp[u], sizeof(dp[u]));
        memset(dp[u], 0x3f, sizeof(dp[u]));
        for (int j = 0; j <= k; j++) {
            for (int t = 0; t <= j; t++) {
                dp[u][j][0] = std::min({dp[u][j][0], dp[v][t][0] + ret[j - t][0] + (m == 2) * w, dp[v][t][1] + ret[j - t][0]});
                dp[u][j][1] = std::min({dp[u][j][1], dp[v][t][1] + ret[j - t][1] + w, dp[v][t][0] + ret[j - t][1]});
            }
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> k;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 1; i < n; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    if (n - k < m - 1) { std::cout << "-1\n"; exit(0); }
    dfs(1, 0);
    std::cout << dp[1][k][1] << "\n";
    return 0;
}
