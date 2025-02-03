#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 7;

int n, m, k, etot;
int head[N], ans[N], bro[N];
bool vis[N];

struct edge {
	int fro, nxt, dat;
} e[N];

struct DSU {
	int fa[N];

	void init(const int n) {
		for (int i = 0; i <= n; i++) {
			fa[i] = i;
			head[i] = -1;
		}
	}

	int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

	void merge(int x, int y) {
		x = find(x), y = find(y);
		if (x == y) return;
		fa[x] = y;
	}
} uni;

void addedge(int u, int v) {
	e[++etot].fro = u, e[etot].nxt = head[u];
	head[u] = etot;
	e[etot].dat = v;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	uni.init(n);
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		addedge(x, y);
		addedge(y, x);
	}
	std::cin >> k;
	for (int i = 1; i <= k; i++) {
		std::cin >> bro[i];
		vis[bro[i]] = 1;
	}
	int tot = n - k;
	for (int i = 1; i <= m * 2; i++) {
		int x = e[i].fro, y = e[i].dat;
		if (!vis[x] && !vis[y] && uni.find(x) != uni.find(y)) {
			tot--;
			uni.merge(x, y);
		}
	}
	ans[k + 1] = tot;
	for (int i = k; i >= 1; i--) {
		tot++;
		vis[bro[i]] = 0;
		for (auto j = head[bro[i]]; j != -1; j = e[j].nxt) {
			if (!vis[e[j].dat] && uni.find(bro[i]) != uni.find(e[j].dat)) {
				tot--;
				uni.merge(bro[i], e[j].dat);
			}
		}
		ans[i] = tot;
	}
	for (int i = 1; i <= k + 1; i++)
		std::cout << ans[i] << "\n";
	return 0;
}
