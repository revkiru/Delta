#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m;
int cnt, mxm, mxx;
int dep[N], dis[N], tag[N];
int t[N], d[N], tu[N], tv[N], fa[20][N];

struct edge {
	int to, val;
};

std::vector<edge> G[N << 1];

void dfs(int x, int lst, int d) {
	fa[0][x] = lst;
	dep[x] = dep[lst] + 1;
	dis[x] = d;
	
	for (size_t i = 0; i < G[x].size(); i++) {
		if (G[x][i].to != lst)
			dfs(G[x][i].to, x, d + G[x][i].val);
	}
}

int lca(int u, int v) {
	if (dep[u] < dep[v])
		std::swap(u, v);
	for (int i = 18; i >= 0; i--)
		if (dep[fa[i][u]] >= dep[v])
			u = fa[i][u];
	if (u == v)
		return u;
	for (int i = 18; i >= 0; i--)
		if (fa[i][u] != fa[i][v]) {
			u = fa[i][u];
			v = fa[i][v];
		}
	return fa[0][u];
}

void dfsc(int x) {
	for (size_t i = 0; i < G[x].size(); i++) {
		if (G[x][i].to != fa[0][x]) {
			dfsc(G[x][i].to);
			tag[x] += tag[G[x][i].to];
		}
	}
	if (tag[x] == cnt)
		mxx = std::max(mxx, dis[x] - dis[fa[0][x]]);
}

bool check(int x) {
	memset(tag, 0, sizeof(tag));
	cnt = 0;
	for (int i = 1; i <= m; i++) {
		if (d[i] > x) {
			tag[tu[i]]++, tag[tv[i]]++;
			tag[t[i]] -= 2;
			cnt++;
		}
	}
	mxx = 0;
	dfsc(1);
	for (int i = 1; i <= m; i++)
		if (d[i] - mxx > x)
			return 0;
	return 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	n = read<int>(), m = read<int>();
	for (int i = 1; i < n; i++) {
		int u = read<int>(), v = read<int>(), w = read<int>();
		mxm = std::max(mxm, w);
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	dfs(1, 0, 0);
	for (int i = 1; i <= 18; i++) {
		for (int j = 1; j <= n; j++)
			fa[i][j] = fa[i - 1][fa[i - 1][j]];
	}
	for (int i = 1; i <= m; i++) {
		tu[i] = read<int>(), tv[i] = read<int>();
		t[i] = lca(tu[i], tv[i]);
		d[i] = dis[tu[i]] + dis[tv[i]] - 2 * dis[t[i]];
		mxx = std::max(mxx, d[i]);
	}
	int l = mxx - mxm, r = mxx, ans = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	write<int>(ans);
	puts("");
	return 0;
}
