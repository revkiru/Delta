#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n, m, v;
    std::cin >> n >> m >> v;
    std::vector<int> a(n + 1);
    std::vector<i64> sum(n + 1);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }

    i64 val = 0;
    std::vector<int> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        val += a[i];
        if (val >= v) {
            pre[i] = pre[i - 1] + 1;
            val = 0;
        } else {
            pre[i] = pre[i - 1];
        }
    }
    val = 0;
    std::vector<int> lst(n + 2);
    for (int i = n; i >= 1; i--) {
        val += a[i];
        if (val >= v) {
            lst[i] = lst[i + 1] + 1;
            val = 0;
        } else {
            lst[i] = lst[i + 1];
        }
    }

    if (pre[n] < m) { std::cout << "-1\n"; return; }
    i64 ans = -1;
    for (int i = 1; i <= n; i++) {
        int req = m - pre[i - 1];
        int _r = std::upper_bound(lst.begin() + i, lst.begin() + n + 2, req, std::greater<int>()) - lst.begin() - 1;
        if (lst[_r] < req) continue;
        ans = std::max(ans, sum[_r - 1] - sum[i - 1]);
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
