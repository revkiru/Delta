#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<i64> a(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        a[i] += a[i - 1];
    }

    i64 mxg = 0, mxs = a[n];
    for (int i = 1; i < n; i++)
        mxg = std::max(mxg, 1ll * std::__gcd(mxs, mxs - a[i]));
    std::cout << mxg << "\n";
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
