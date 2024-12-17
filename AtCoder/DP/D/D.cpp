#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, w;
i64 dp[N];

struct node {
    int w, v;
} a[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> w;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i].w >> a[i].v;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = w; j >= a[i].w; j--)
            dp[j] = std::max(dp[j], dp[j - a[i].w] + a[i].v);
    }
    std::cout << dp[w] << "\n";
    return 0;
}
