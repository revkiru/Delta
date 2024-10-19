#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 15;
constexpr i64 I = 1e10;

i64 l, r, num[12];
i64 dp[N][N][N][2][2][2][2];

i64 dfs(int p, int a, int b, int f0, int f1, int _4, int _8) {
    if (_4 && _8) { return 0; }
    if (p <= 0) return f0;
    if (~dp[p][a][b][f0][f1][_4][_8]) return dp[p][a][b][f0][f1][_4][_8];
    i64 ret = 0;
    int lim = !f1 ? num[p] : 9;
    for (int i = 0; i <= lim; i++)
        ret += dfs(p - 1, i, a, f0 || (i == b && i == a), f1 || (i < lim), _4 || (i == 4), _8 || (i == 8));
    return dp[p][a][b][f0][f1][_4][_8] = ret;
}

i64 solve(i64 x) {
    if (x < I) return 0;
    memset(dp, -1, sizeof(dp));
    int len = 0;
    while (x) { num[++len] = x % 10; x /= 10; }
    // 手算第一位
    i64 ret = 0;
    for (int i = 1; i <= num[len]; i++)
        ret += dfs(10, i, 0, 0, (i < num[len]), i == 4, i == 8);
    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> l >> r;
    std::cout << solve(r) - solve(l - 1) << "\n";
    return 0;
}
