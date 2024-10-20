#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e3 + 7;
constexpr int P = 1e9 + 7;
const int dx[] = {0, 1, 0};
const int dy[] = {1, 0, -1};

int n, m, ans = 1;
int fa[N * N], dp[N * N];
bool vis[N * N];
std::string c[N];

namespace DSU {
    int find(int x) { return (fa[x] == x) ? fa[x] : fa[x] = find(fa[x]); }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        fa[x] = y;
        dp[y] = dp[x] * dp[y] % P;
    }
}

int _hash(int x, int y) { return (x - 1) * std::max(n, m) + y; }

bool lg(int x, int y) { return x > 1 && x < n && y > 1 && y < m && c[x][y] != '#'; }

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= (int) 1e6; i++) { fa[i] = i; dp[i] = 1; }
    for (int i = 1; i <= n; i++) {
        std::cin >> c[i];
        c[i] = '$' + c[i];
    }
    for (int i = n - 1; i > 1; i--) {
        for (int j = 2; j < m; j++) {
            if (c[i][j] != '#') {
                for (int k = 0; k < 3; k++) {
                    int nx = i + dx[k], ny = j + dy[k];
                    if (lg(nx, ny))
                        DSU::unite(_hash(i, j), _hash(nx, ny));
                }
            }
        }
        for (int j = 2; j < m; j++) {
            if (c[i][j] != '#') {
                int t = DSU::find(_hash(i, j));
                if (vis[t]) continue;
                vis[t] = 1;
                dp[t] = (dp[t] + 1) % P;
            }
        }
        for (int j = 2; j < m; j++)
            if (c[i][j] != '#')
                vis[DSU::find(_hash(i, j))] = 0;
    }
    for (int i = 2; i < n; i++) {
        for (int j = 2; j < m; j++) {
            if (c[i][j] != '#') {
                int h = _hash(i, j);
                if (h == fa[h])
                    ans = ans * dp[h] % P;
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}
