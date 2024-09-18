#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, ans;
int p[N], c[N];
std::vector<int> G[N << 1];

void dfs(int u, int clr, int lst) {
    if (clr != c[u]) {
        ans++;
        clr = c[u];
    }
    for (auto i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if (v == lst) continue;
        dfs(v, clr, u);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("color.in", "r", stdin);
    // freopen("color.out", "w", stdout);

    std::cin >> n;
    for (int i = 1; i < n; i++) {
        std::cin >> p[i];
        G[i + 1].push_back(p[i]);
        G[p[i]].push_back(i + 1);
    }
    for (int i = 1; i <= n; i++) {
        std::cin >> c[i];
    }
    dfs(1, 0, -1);
    std::cout << ans << "\n";
    return 0;
}
