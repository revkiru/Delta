#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2007;

int n, k, cnt;
i64 sta[N], sit[N], f[17][N][107];

void dfs(int x, int num, int cur) {
    if (cur >= n) {
        sit[++cnt] = x;
        sta[cnt] = num;
        return;
    }
    dfs(x, num, cur + 1);
    dfs(x + (1 << cur), num + 1, cur + 2);
}

bool able(int j, int x) {
    if (sit[j] & sit[x]) return 0;
    if ((sit[j] << 1) & sit[x]) return 0;
    if (sit[j] & (sit[x] << 1)) return 0;
    return 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    dfs(0, 0, 0);
    for (int j = 1; j <= cnt; j++)
        f[1][j][sta[j]] = 1;
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= cnt; j++) {
            for (int x = 1; x <= cnt; x++) {
                if (!able(j, x)) continue;
                for (int l = sta[j]; l <= k; l++)   
                    f[i][j][l] += f[i - 1][x][l - sta[j]];
            }
        }
    }
    i64 ans = 0;
    for (int i = 1; i <= cnt; i++)
        ans += f[n][i][k];
    std::cout << ans << "\n";
    return 0;
}
