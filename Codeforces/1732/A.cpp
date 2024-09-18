#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, g;
int a[N];

void solve() {
    std::cin >> n;
    g = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        g = std::__gcd(g, a[i]);
    }

    if (g == 1) { std::cout << "0\n"; }
    else if (std::__gcd(g, std::__gcd(a[n], n)) == 1) { std::cout << "1\n"; }
    else if (std::__gcd(g, std::__gcd(a[n - 1], n - 1)) == 1) { std::cout << "2\n"; }
    else std::cout << "3\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("unite.in", "r", stdin);
    // freopen("unite.out", "w", stdout);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
