#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, ans;
int a[N];
std::string s;

void solve() {
    std::cin >> n;
    std::cin >> s;
    for (int i = 0; i < s.size(); i++)
        a[i] = s[i] - '0';
    for (int i = n; i >= 1; i--)
        a[i] ^= a[i - 1];
    std::cout << std::max(0, std::accumulate(a + 1, a + n + 1, -1)) << "\n";
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("reverse.in", "r", stdin);
    // freopen("reverse.out", "w", stdout);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
