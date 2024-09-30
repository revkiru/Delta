#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int B = 550;

int n, m;
int x[N], y[N], a[N], p[N];
int buc[B][B];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        std::cin >> x[i] >> y[i];
    for (int i = 1; i <= m; i++) {
        int op, k, c, ans = 0;
        std::cin >> op >> k;
        c = x[k] + y[k];
        if (op == 1) {
            a[k] = i;
            if (c < B) {
                for (int j = 0; j < c; j++)
                    buc[c][(i + j) % c] += (j >= x[k]);
            } else {
                for (int j = i + x[k]; j <= m; j += c) {
                    p[j]++;
                    p[std::min(m + 1, j + y[k])]--;
                }
            }
        } else {
            if (c < B) {
                for (int j = 0; j < c; j++)
                    buc[c][(a[k] + j) % c] -= (j >= x[k]);
            } else {
                for (int j = a[k] + x[k]; j <= m; j += c) {
                    p[std::max(i, j)]--;
                    p[std::max(i, std::min(m + 1, j + y[k]))]++;
                }
            }
        }
        for (int j = 2; j < B; j++)
            ans += buc[j][i % j];
        std::cout << ans + (p[i] += p[i - 1]) << "\n";
    }
    return 0;
}
