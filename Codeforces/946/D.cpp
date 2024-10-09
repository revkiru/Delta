#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 507;

int n, m, k;
int a[N], s[N];
int mn[N][N], f[N][N];

int main() {
    scanf("%d %d %d", &n, &m, &k);
    memset(mn, 0x3f, sizeof(mn));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char ch;
            scanf(" %c", &ch);
            if (ch == '1')
                a[++s[i]] = j;
        }
        // printf("%d ", s[i]);
        mn[i][s[i]] = 0;
        for (int len = 1; len <= s[i]; len++) {
            for (int l = 1; l + len - 1 <= s[i]; l++) {
                int r = l + len - 1;
                mn[i][s[i] - len] = std::min(mn[i][s[i] - len], a[r] - a[l] + 1);
                // printf("%d ", mn[i][s[i] - len]);
            }
            // puts("");
        }
    }
    // puts("");
    memset(f, 0x3f, sizeof(f));
    for (int i = 0; i <= k; i++)
        f[0][i] = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++)
            for (int p = 0; p <= std::min(j, s[i]); p++)
                f[i][j] = std::min(f[i][j], f[i - 1][j - p] + mn[i][p]);
    }
    printf("%d\n", f[n][k]);
    return 0;
}
