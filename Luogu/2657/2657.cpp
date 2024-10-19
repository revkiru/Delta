#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 15;

int L, R, len;
int a[N];
i64 ans, mx, mn;
i64 dp[N][N];

i64 dfs(int pos, int pre, int f0, int lim) {
    if (pos > len) return 1;
    if (pre != -2 && !lim && ~dp[pos][pre]) return dp[pos][pre];
    i64 ret = 0;
    int res = lim ? a[len - pos + 1] : 9;
    for (int i = 0; i <= res; i++) {
        if (std::abs(i - pre) < 2)
            continue;
        if (f0 && !i)
            ret += dfs(pos + 1, -2, 1, lim && i == res);
        else
            ret += dfs(pos + 1, i, 0, lim && i == res);
    }
    if (!lim && !f0)
        dp[pos][pre] = ret;
    return ret;
}

void solve(int x) {
    len = 0;
    while (x) { a[++len] = x % 10; x /= 10; }
    memset(dp, -1, sizeof(dp));
    ans = dfs(1, -2, 1, 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> L >> R;
    solve(L - 1);
    mn = ans;
    solve(R);
    mx = ans;
    std::cout << mx - mn << "\n";
    return 0;
}
