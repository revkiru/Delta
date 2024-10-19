#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, k, q;
i64 ans[N];

struct node {
    int clr, prt;
} col[N], row[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("color.in", "r", stdin);
    // freopen("color.out", "w", stdout);

    std::cin >> n >> m >> k >> q;
    for (int i = 1; i <= n; i++) {
        int opt, x, c;
        std::cin >> opt >> x >> c;
        if (opt == 0) {
            row[x].clr = c;
            row[x].prt = i;
        } else {
            col[x].clr = c;
            col[x].prt = i;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (row[i].prt > col[j].prt)
                ans[row[i].clr]++;
            else
                ans[col[j].clr]++;
        }
    }
    for (int i = 1; i <= k; i++)
        std::cout << ans[i] << " ";
    std::cout << "\n";
    return 0;
}
