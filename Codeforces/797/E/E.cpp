#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int B = 350;

int n, m, b;
int a[N], s[N][B];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    b = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= b; i++) {
        for (int j = n; j; j--)
            s[j][i] = (j + a[j] + i) > n ? 1 : (s[j + a[j] + i][i] + 1);
    }
    std::cin >> m;
    for (int i = 1; i <= m; i++) {
        int p, k;
        std::cin >> p >> k;
        if (k <= b)
            std::cout << s[p][k] << "\n";
        else {
            int ret = 0;
            while (p <= n) {
                ret++;
                p += (a[p] + k);
            }
            std::cout << ret << "\n";
        }
    }
    return 0;
}
