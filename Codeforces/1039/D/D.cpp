#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int B = 600;

int n, t0t;
int ans[N], fa[N], f[N], idx[N];
std::vector<int> G[N];

void dfs(int u, int lst) {
	fa[u] = lst;
	for (auto v : G[u]) {
		if (v != lst)
			dfs(v, u);
	}
	idx[++t0t] = u;
}

int solve(int k) {
	int ret = 0;
	f[0] = -1;
	for (int i = 1; i <= n; i++)
		f[i] = 1;
	for (int i = 1; i <= n; i++) {
		int x = idx[i];
		if (f[fa[x]] != -1 && f[x] != -1) {	// exsit
			if (f[x] + f[fa[x]] >= k) {
				ret++;
				f[fa[x]] = -1;
			} else {
				f[fa[x]] = std::max(f[fa[x]], f[x] + 1);
			}
		}
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v;
		std::cin >> u >> v;
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}

	ans[1] = n;
	dfs(1, 0);

	for (int k = 2; k <= B; k++)
		ans[k] = solve(k);
	for (int k = B + 1; k <= n;) {
		int l = k - 1, r = n + 1, ret = solve(k);
		while (l + 1 != r) {
			int mid = (l + r) >> 1;
			if (ret == solve(mid))
				l = mid;
			else
				r = mid;
		}
		for (int i = k; i <= l; i++)
			ans[i] = ret;
		k = r;
	}

	for (int i = 1; i <= n; i++)
		std::cout << ans[i] << "\n";
	return 0;
}
