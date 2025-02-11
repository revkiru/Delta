#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n + 1, std::vector<int>(n + 1));
    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        s = '$' + s;
        for (int j = 1; j <= n; j++)
            g[i][j] = s[j] - '0';
    }
    std::vector<int> p(n + 1);
    std::iota(p.begin() + 1, p.end(), 1);
    
    auto cmp = [&](int x, int y) -> bool {
        if (g[x][y] == 1)
            return x < y;
        return x > y;
    };
    std::sort(p.begin() + 1, p.end(), cmp);

    for (int i = 1; i <= n; i++)
        std::cout << p[i] << " ";
    std::cout << "\n";
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
