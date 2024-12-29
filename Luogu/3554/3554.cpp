#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n, k;
int f[N];
std::vector<int> G[N << 1];

void dfs(int u, int fa) {
	int siz = 0, cnt = 0;
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v == fa)
			continue;
		dfs(v, u);
		siz++;
		cnt += f[v];
	}
	f[u] = std::max(0, siz - k + cnt);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x, y; i < n; i++) {
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}

	int l = 0, r = n, ans = 0;
	while (l < r) {
		k = (l + r) >> 1;
		dfs(1, 0);
		if (f[1]) {
			l = k + 1;
		} else {
			r = k;
			ans = k;
		}
	}

	std::cout << ans << "\n";
	return 0;
}
