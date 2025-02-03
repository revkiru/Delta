#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, m;

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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	uni.init(n);
	for (int i = 1, opt, x, y; i <= m; i++) {
		std::cin >> opt >> x >> y;
		switch (opt) {
			case 1:
				uni.merge(x, y);
				break;
			case 2:
				std::cout << (uni.find(x) == uni.find(y) ? "Y" : "N") << "\n";
				break;
			default:
				break;
		}
	}
	return 0;
}
