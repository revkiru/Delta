#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, a, b;
    std::cin >> n >> a >> b;
    std::string s;
    std::cin >> s;
    int nx = 0, ny = 0;
    for (int c = 1; c < 100; c++) {
        for (size_t i = 0; i < s.size(); i++) {
            if (nx == a && ny == b) {
                std::cout << "YES\n";
                return;
            }
            if (s[i] == 'N') ny++;
            if (s[i] == 'S') ny--;
            if (s[i] == 'E') nx++;
            if (s[i] == 'W') nx--;
        }
    }
    std::cout << "NO\n";
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
