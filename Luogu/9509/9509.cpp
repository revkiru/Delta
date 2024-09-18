#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = ((int) 5e6 >> 1) + 7;

int n;
int a[N], f[2][N];
std::bitset<N> s, b, c;

void solve() {
    std::cin >> n;
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        sum += a[i];
    }
    a[n + 1] = 0;
    if (sum % n == 0) {
        int p = sum / n;
        s.reset();
        s.set(0);
        b.reset();
        b.set(0);
        for (int i = 1; i <= n; i++) {
            a[i] -= p;
            if (a[i] == 0) {
                std::cout << "Yes\n";
                return;
            }
            if (a[i] > 0) {
                b |= (b << a[i]);
            } else {
                s |= (s << (-a[i]));
            }
        }
        c = s & b;
        if (c.count() > 2)
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    } else {
        std::cout << "No\n";
    }
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
