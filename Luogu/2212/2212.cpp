#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;

int n, m, k, ecnt, ans;
std::pair<int, int> G[N];

struct edge {
	int u, v, w;
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
	return x.w < y.w;
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
	uni.init(n);
	for (int i = 1; i <= n; i++) {
		std::cin >> G[i].first >> G[i].second;
		for (int j = 1; j < i; j++) {
			int d = (G[i].first - G[j].first) * (G[i].first - G[j].first) + (G[i].second - G[j].second) * (G[i].second - G[j].second);
			if (d >= m) {
				e[++k] = {i, j, d};
			}
		}
	}
	kruskal();
	if (ecnt == n - 1)
		std::cout << ans << "\n";
	else
		std::cout << "-1\n";
	return 0;
}
