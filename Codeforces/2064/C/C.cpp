#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];

    std::vector<i64> pre(n + 2), suf(n + 2);
    pre[1] = a[1] > 0 ? a[1] : 0;
    for (int i = 2; i <= n; i++) {
        pre[i] = pre[i - 1];
        pre[i] += a[i] > 0 ? a[i] : 0;
    }
    suf[n] = a[n] < 0 ? -a[n] : 0;
    for (int i = n - 1; i >= 1; i--) {
        suf[i] = suf[i + 1];
        suf[i] -= a[i] < 0 ? a[i] : 0;
    }

    i64 ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, pre[i] + suf[i]);
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
