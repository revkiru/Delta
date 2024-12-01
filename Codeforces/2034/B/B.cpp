#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, k;
    std::string s;
    std::cin >> n >> m >> k;
    std::cin >> s;

    int ans = 0, cov = 0, len = 0;
    for (int i = 0; i < n; i++) {
        if (i >= cov && s[i] == '0') len++;
        else len = 0;
        if (len == m) {
            ans++;
            len = 0;
            cov = i + k;
        }
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
