#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::string s[n + 1];
    for (int i = 1; i <= n; i++) {
        std::cin >> s[i];
        s[i] = '$' + s[i];
    }

    std::vector<std::pair<int, int>> maz[n + 2][m + 2];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == 'U') maz[i - 1][j].push_back({i, j});
            if (s[i][j] == 'D') maz[i + 1][j].push_back({i, j});
            if (s[i][j] == 'L') maz[i][j - 1].push_back({i, j});
            if (s[i][j] == 'R') maz[i][j + 1].push_back({i, j});
        }
    }

    std::vector<std::vector<int>> vis(n + 2, std::vector<int>(m + 2));
    std::queue<std::pair<int, int>> q;
    for (int i = 1; i <= m; i++) { vis[0][i] = 1; q.push({0, i}); }
    for (int i = 1; i <= m; i++) { vis[n + 1][i] = 1; q.push({n + 1, i}); }
    for (int i = 1; i <= n; i++) { vis[i][0] = 1; q.push({i, 0}); }
    for (int i = 1; i <= n; i++) { vis[i][m + 1] = 1; q.push({i, m + 1}); }

    while (q.size()) {
        auto [i, j] = q.front();
        q.pop();
        for (auto [a, b] : maz[i][j]) {
            if (!vis[a][b]) {
                vis[a][b] = 1;
                q.push({a, b});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s[i][j] == '?' && vis[i - 1][j] && vis[i + 1][j] && vis[i][j - 1] && vis[i][j + 1])
                vis[i][j] = 1;
        }
    }

    int ans = n * m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            if (vis[i][j])
                ans--;
    }
    std::cout << ans << "\n";
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
