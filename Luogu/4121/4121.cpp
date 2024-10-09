#include <bits/stdc++.h>

using i64 = long long;

#define loc(x, y) ((x - 1) * n + y)

constexpr int N = 207;
const int dx[] = {0, 1, 0, -1, 0};
const int dy[] = {0, 0, -1, 0, 1};

int n, m, cnt;
int ans[2], gr[N][N], pr[N][N];

struct undoProject {
    int pos, val;
};

std::stack<undoProject> st;

struct ques {
    int l, r, val, x, y;
} q[N * N << 1];

struct DSU {
    int fa[N * N], siz[N * N];

    void init() {
        cnt = n * n;
        for (int i = 1; i <= n * n; i++) {
            fa[i] = i;
            siz[i] = 1;
        }
    }

    int find(int x) { if (fa[x] == x) return x; return find(fa[x]); }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (siz[x] > siz[y])
            std::swap(x, y);
        st.push({x, (siz[x] == siz[y])});
        fa[x] = y;
        siz[x] += (siz[x] == siz[y]);
    }

    void undo() {
        int x = st.top().pos;
        siz[fa[x]] -= st.top().val;
        fa[x] = x;
        st.pop();
    }
} dsu;

std::vector<int> G[N * N << 2];

void update(int o, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        G[o].push_back(v);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid)
        update(o << 1, l, mid, ql, qr, v);
    if (qr > mid)
        update(o << 1 | 1, mid + 1, r, ql, qr, v);
}

void solve(int i, int l, int r) {
    size_t level = st.size(), ans0 = ans[0], ans1 = ans[1];
    for (auto u : G[i]) {
        ans[q[u].val]++;
        gr[q[u].x][q[u].y] = q[u].val;
        for (int j = 1; j <= 4; j++) {
            int nx = q[u].x + dx[j], ny = q[u].y + dy[j];
            if (nx <= 0 || nx > n || ny <= 0 || ny > n) continue;
            if (gr[q[u].x][q[u].y] == gr[nx][ny]) {
                int x = dsu.find(loc(q[u].x, q[u].y));
                int y = dsu.find(loc(nx, ny));
                if (x == y) continue;
                --ans[q[u].val];
                dsu.unite(x, y);
            }
        }
    }
    if (l == r)
        printf("%d %d\n", ans[1], ans[0]);
    else {
        int mid = (l + r) >> 1;
        solve(i << 1, l, mid);
        solve(i << 1 | 1, mid + 1, r);
    }
    for (auto u : G[i])
        gr[q[u].x][q[u].y] = -1;
    ans[0] = ans0, ans[1] = ans1;
    while (st.size() > level) {
        dsu.undo();
    }
}

int main() {
    scanf("%d", &n);
    dsu.init();
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            scanf("%d", &gr[i][j]);
    scanf("%d", &m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            q[loc(i, j)] = {1, m, gr[i][j], i, j};
            pr[i][j] = loc(i, j);
        }
    for (int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        q[pr[x][y]].r = i - 1;
        q[++cnt] = {i, m, gr[x][y] ^= 1, x, y};
        pr[x][y] = cnt;
    }
    for (int i = 1; i <= cnt; i++)
        if (q[i].l <= q[i].r)
            update(1, 1, m, q[i].l, q[i].r, i);
    memset(gr, -1, sizeof(gr));
    solve(1, 1, m);
    return 0;
}
