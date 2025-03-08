#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, m, k;
int ecnt, ans, cnt;

struct edge {
	int u, v, w;
} e[N];

bool cmp(const edge &a, const edge &b) { return a.w < b.w; }

struct DSU {
	int fa[N], siz[N];

	void init(const int n) {
		for (int i = 1; i <= n; i++) {
			fa[i] = i;
			siz[i] = 1;
		}
	}

	int find(int x) { return (fa[x] == x ? fa[x] : fa[x] = find(fa[x])); }

	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return;
		if (siz[x] < siz[y]) std::swap(x, y);
		fa[y] = x;
		siz[x] += siz[y];
	}
} uni;

void kruskal() {
	std::sort(e + 1, e + k + 1, cmp);
	for (int i = 1; i <= k - cnt; i++) {
		auto [u, v, w] = e[i];
		u = uni.find(u), v = uni.find(v);
		if (u == v) continue;
		uni.merge(u, v);
		ecnt++, ans += w;
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	uni.init(m);
	for (int i = 1, x; i <= m; i++) {
		for (int j = 1; j <= m; j++) {
			std::cin >> x;
			if (i >= j || x == 0) continue;
			e[++k] = {i, j, x};
			if (x > n) cnt++;
		}
	}
	kruskal();
	if (ecnt == m - 1) { std::cout << ans + n << "\n"; }
	else { std::cout << ans + (m - ecnt) * n << "\n"; }
	return 0;
}
