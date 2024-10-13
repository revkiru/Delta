#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 6e3 + 7;

int n;
int r[N], vis[N], dp[N][2];
std::vector<int> G[N << 1];

void dfs(int u) {
    dp[u][0] = 0;
    dp[u][1] = r[u];
    for (size_t i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        dfs(v);
        dp[u][0] += std::max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> r[i];
    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        G[y].push_back(x);
        vis[x] = 1;
    }

    int rt;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            rt = i;
            break;
        }
    }

    dfs(rt);
    std::cout << std::max(dp[rt][0], dp[rt][1]) << "\n";
    return 0;
}
