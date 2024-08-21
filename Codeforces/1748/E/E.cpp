#include <bits/stdc++.h>
 
using i64 = long long;
 
constexpr int P = 1e9 + 7;
 
void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> p(n + 1);
	for (int i = 1; i <= n; i++)
		std::cin >> p[i];
	
	int t0t = 0;
	std::vector<i64> stc((n + m) + 1), lc((n + m) << 1), rc((n + m) << 1);
	for (int i = 1; i <= n; i++) {
		int top = t0t;
		while (top && p[stc[top]] < p[i])
			top--;
		if (top) rc[stc[top]] = i;
		if (top < t0t) lc[i] = stc[top + 1];
		stc[t0t = ++top] = i;
	}
 
	std::vector<std::vector<i64>> f(n + 1, std::vector<i64>(m + 1));
	std::function<void(int)> dfs = [&](int u) {
		for (int i = 1; i <= m; i++) { f[u][i] = 1; }
		if (lc[u]) dfs(lc[u]);
		if (rc[u]) dfs(rc[u]);
		if (lc[u]) {
			for (int i = 1; i <= m; i++)
				f[u][i] = f[u][i] * f[lc[u]][i - 1] % P;
		}
		if (rc[u]) {
			for (int i = 1; i <= m; i++)
				f[u][i] = f[u][i] * f[rc[u]][i] % P;
		}
		for (int i = 2; i <= m; i++)
			f[u][i] = (f[u][i] + f[u][i - 1]) % P;
	};
	
	dfs(stc[1]);
	std::cout << f[stc[1]][m] << "\n";
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
