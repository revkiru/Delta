#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;

int n, m, k, ecnt;
double ans;
std::pair<int, int> G[N];

struct edge {
	int u, v;
	double w;
} e[N];

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

bool cmp(const edge &x, const edge &y) {
	if (x.w == y.w) return x.u < y.u;
	return x.w < y.w;
}

double calc(int i, int j) {
	return (double) (std::sqrt((double) (G[i].first - G[j].first) * (G[i].first - G[j].first) + (double) (G[i].second - G[j].second) * (G[i].second - G[j].second)));
}

void kruskal() {
	std::sort(e + 1, e + k + 1, cmp);
	for (int i = 1; i <= k; i++) {
		auto [u, v, w] = e[i];
		u = uni.find(u), v = uni.find(v);
		if (u == v) continue;
		uni.merge(u, v);
		ecnt++, ans += w;
		if (ecnt == n - 1) break;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> G[i].first >> G[i].second;
	}
	uni.init(n);
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			double dis = calc(i, j);
			e[++k] = {i, j, dis};
		}
	}
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		e[++k] = {x, y, 0.0};
	}
	kruskal();
	std::cout << std::fixed << std::setprecision(2) << ans << "\n";
	return 0;
}
