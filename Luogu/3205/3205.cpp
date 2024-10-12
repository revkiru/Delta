#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1007;
constexpr int P = 19650827;

int n;
int a[N << 1], f[N << 1][N << 1][2];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    for (int i = 1; i <= n; i++)
        f[i][i][0] = 1;
    for (int len = 1; len <= n; len++) {
        for (int i = 1, j = i + len; j <= n; i++, j++) {
            if (a[i] < a[i + 1])
                (f[i][j][0] += f[i + 1][j][0]) %= P;
            if (a[i] < a[j])
                (f[i][j][0] += f[i + 1][j][1]) %= P;
            if (a[j] > a[i])
                (f[i][j][1] += f[i][j - 1][0]) %= P;
            if (a[j] > a[j - 1])
                (f[i][j][1] += f[i][j - 1][1]) %= P;
        }
    }
    std::cout << (f[1][n][0] + f[1][n][1]) % P << "\n";
    return 0;
}
