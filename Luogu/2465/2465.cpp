#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1 << 12;
constexpr int M = 200;

int n, m, t;
int etot, head[M];
int val[N], dp[M][N], cst[20];

struct edge {
    int to, nxt;
} e[M << 1];

void addedge(int u,int v) {
    e[++etot].to = v;
    e[etot].nxt = head[u];
    head[u] = etot;
}

void dfs(int u, int fa) {
    for (int i = head[u]; i; i = e[i].nxt){
        int v = e[i].to;
        if (v != fa) {
            dfs(v, u);
            for (int j = (1 << m) - 1; j; j--)
                for (int k = j; k; k = (k - 1) & j)
                    dp[u][j] = std::max(dp[u][j], dp[j][j ^ k] + dp[v][k]);
        }
    }
    for (int i = (1 << m) - 1; i; i--)
        dp[u][i] += val[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1, u, v; i < n; i++){
        std::cin >> u >> v;
        addedge(u, v);
        addedge(v, u);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++)
            std::cin >> cst[j];
        dp[i][0] = 0;
        for (int j = 1; j < (1 << m); j++) {
            int lb = j & (-j);
            int ld = (std::log(lb) + 0.001) / std::log(2);
            dp[i][j] = dp[i][j ^ lb] - cst[ld];
        }
    }
	
	std::cin >> t;
    while (t--) {
        int v, cnt, s = 0;
        std::cin >> v >> cnt;
        for (int j = 1, g; j <= cnt; j++){
            std::cin >> g;
            s |= 1 << (g - 1);
        }
        int mxm = (1 << m) - 1, u = s ^ mxm;
        val[s] += v;
        for (int j = u; j; j = (j - 1) & u)
            val[s | j] += v;
    }
    dfs(1, 0);
    std::cout << dp[1][(1 << m) - 1] << "\n";
    return 0;
}