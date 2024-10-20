#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;
constexpr int S = 10;

int q, s;
int c[S], d[S], f[N];

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    for (int i = 0; i < 4; i++)
        std::cin >> c[i];
    std::cin >> q;
    f[0] = 1;
    for (int j = 0; j < 4; j++) {
        for (int i = c[j]; i < N; i++)
            f[i] += f[i - c[j]];
    }
    while (q--) {
        for (int j = 0; j < 4; j++)
            std::cin >> d[j];
        std::cin >> s;
        int ans = f[s];
        for (int i = 1; i <= 15; i++) {
            int now = s;
            int j = 0, k = 0;
            for (int t = i; t; t >>= 1, j++) {
                if (t & 1) {
                    k ^= 1;
                    now -= (d[j] + 1) * c[j];
                }
            }
            if (now >= 0)
                k ? ans -= f[now] : ans += f[now];
        }
        std::cout << ans << "\n";
    }
    return 0;
}
