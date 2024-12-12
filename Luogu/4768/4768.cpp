#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 7;

int t, n, m, q, k, s;
int h[N], dis[N], fa[20][N], mnd[N];

struct edge {
    int u, v, l, a;

    friend bool operator < (const edge &a, const edge &b) {
        return a.a > b.a;
    }
} e[N];

struct node {
    int u, d;

    friend bool operator < (const node &a, const node &b) {
        return a.d > b.d;
    }
};

struct DSU {
    int fa[N];

    int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }
} uni;

std::vector<int> T[N];
std::vector<std::pair<int, int>> E[N];

void Dij() {
    std::priority_queue<node> _q;
    memset(dis, 0x7f, sizeof(dis));
    _q.push({1, 0});
    dis[1] = 0;

    while (!_q.empty()) {
        int u = _q.top().u, d = _q.top().d;
        _q.pop();
        if (d != dis[u]) continue;
        for (auto j : E[u]) {
            int v = j.first, w = j.second;
            if (d + w < dis[v])
                _q.push({v, dis[v] = d + w});
        }
    }
}

void dfs(int u, int pa) {
    fa[0][u] = pa;
    for (int i = 1; i <= 18; i++)
        fa[i][u] = fa[i - 1][fa[i - 1][u]];
    for (auto v : T[u]) {
        dfs(v, u);
        mnd[u] = std::min(mnd[u], mnd[v]);
    }
}

int jump(int u, int hg) {
    for (int i = 18; ~i; i--)
        if (h[fa[i][u]] > hg)
            u = fa[i][u];
    return u;
}

void exKruskal() {
    std::sort(e + 1, e + m + 1);
    int etot = n;
    for (int i = 1; i < (n << 1); i++) { uni.fa[i] = i; T[i].clear(); }
    for (int i = 1; i <= m; i++) {
        int u = e[i].u, v = e[i].v;
        int fu = uni.find(u), fv = uni.find(v);
        if (fu != fv) {
            h[++etot] = e[i].a;
            T[etot].push_back(fu);
            uni.fa[fu] = etot;
            T[etot].push_back(fv);
            uni.fa[fv] = etot;
        }
    }
    for (int i = 1; i <= n; i++)
        mnd[i] = dis[i];
    for (int i = n + 1; i <= etot; i++)
        mnd[i] = 1e9;
    dfs(etot, 0);
}

void solve() {
	std::cin >> n >> m;
    for (int i = 1; i <= n; i++)
        E[i].clear();
    for (int i = 1, u, v, l, a; i <= m; i++) {
        std::cin >> u >> v >> l >> a;
        e[i] = {u, v, l, a};
        E[u].push_back({v, l});
        E[v].push_back({u, l});
    }

    Dij();
    exKruskal();

    std::cin >> q >> k >> s;
    int ans = 0;
    for (int i = 1, v, p; i <= q; i++) {
        std::cin >> v >> p;
        v = (v + k * ans - 1) % n + 1;
        p = (p + k * ans) % (s + 1);
        std::cout << (ans = mnd[jump(v, p)]) << "\n";
    }
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

    // freopen("return.in", "r", stdin);
    // freopen("return.out", "w", stdout);

	std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
