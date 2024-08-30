#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

/* pl 为 < len 的指针，pr 为 >= len 的指针  */

int n, l;
int a[N], pl[N], pr[N];
std::vector<int> G[N];

void multiClear() {
	for (int i = 1; i <= n; i++) {
		pl[i] = pr[i] = 0;
		G[i].clear();
	}
	n = 0, l = 0;
}

void solve() {
	std::cin >> n >> l;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];

	i64 ans = 0;
	int lst = n + 1;	// 相同对靠后元素的下标
	for (int i = n; i >= 1; i--) {
		G[a[i]].push_back(i);
		while (G[a[i]][pr[a[i]]] >= lst)
			pr[a[i]]++;
		if (pl[a[i]] < pr[a[i]])
			pl[a[i]] = pr[a[i]];
		while (pl[a[i]] < G[a[i]].size() && G[a[i]][pl[a[i]]] - i + 1 >= l)
			pl[a[i]]++;
		if (lst - i >= l)
			ans += lst - i - l + 1 + (pr[a[i]] - pl[a[i]]);
		if (a[i] == a[i - 1])
			lst = i;
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		multiClear();
		solve();
	}
	return 0;
}
