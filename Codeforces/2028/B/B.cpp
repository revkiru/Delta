#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    i64 n, b, c;
    std::cin >> n >> b >> c;
    i64 ans = -1;
    if (c >= n)
        ans = n;
    else if (b)
        ans = n - (n - c - 1) / b - 1;
    else if (n >= c + 3)
        ans = -1;
    else
        ans = n - 1;
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
