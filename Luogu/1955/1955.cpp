#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int M = 2e6 + 7;

int n, bt, ct;

struct node {
	int x, y, z;
} a[N];

int b[M], c[M];

struct DSU {
	int fa[M];

	void init(const int n) { for (int i = 1; i <= n; i++) fa[i] = i; }

	int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return;
		fa[x] = y;
	}
} uni;

void solve() {
	std::cin >> n;
	bt = ct = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i].x >> a[i].y >> a[i].z;
		b[++bt] = a[i].x;
		b[++bt] = a[i].y;
	}

	std::sort(b + 1, b + bt + 1);
	for (int i = 1; i <= bt; i++) {
		if (b[i] != b[i - 1])
			c[++ct] = b[i];
	}
	for (int i = 1; i <= n; i++) {
		a[i].x = std::lower_bound(c + 1, c + ct + 1, a[i].x) - c;
		a[i].y = std::lower_bound(c + 1, c + ct + 1, a[i].y) - c;
	}

	uni.init(ct);
	for (int i = 1; i <= n; i++) {
		if (a[i].z)
			uni.merge(a[i].x, a[i].y);
	}
	bool flg = 1;
	for (int i = 1; i <= n; i++) {
		if (!a[i].z) {
			if (uni.find(a[i].x) == uni.find(a[i].y)) {
				flg = 0;
				break;
			}
		}
	}
	std::cout << (flg ? "YES" : "NO") << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
