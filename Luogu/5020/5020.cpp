#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int R = 25007;

int t, n;
int a[N], dp[R];

void solve() {
    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    std::sort(a + 1, a + n + 1);
    memset(dp, 0, sizeof(dp));

    int ans = n;
    dp[0] = 1;
    for (int i = 1; i <= n; i++) {
        if (dp[a[i]]) {
            ans--;
            continue;
        }
        for (int j = a[i]; j <= a[n]; j++)
            dp[j] = dp[j] | dp[j - a[i]];
    }
    std::cout << ans << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
