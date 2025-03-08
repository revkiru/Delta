#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int M = 5e5 + 7;

int n, m;
int ecnt, ans;

struct edge {
	int u, v, w;
} e[M];

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
	std::sort(e + 1, e + m + 1, cmp);
	for (int i = 1; i <= m; i++) {
		int u = uni.find(e[i].u), v = uni.find(e[i].v);
		if (u == v) continue;
		ans += e[i].w, ecnt++;
		uni.merge(u, v);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	uni.init(n);
	for (int i = 1; i <= m; i++) {
		std::cin >> e[i].u >> e[i].v >> e[i].w;
	}
	kruskal();
	if (ecnt == n - 1) std::cout << ans << "\n";
	else std::cout << "orz\n";
	return 0;
}
