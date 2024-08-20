#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, q, s, t;
int lst, ans;
int a[N];

int delta(int &x) { return x > 0 ? -(x * s) : -(x * t); }

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q >> s >> t;
	std::cin >> lst;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		a[i] = x - lst;
		lst = x;
		ans += delta(a[i]);
	}
	for (int i = 1; i <= q; i++) {
		int x, y, z;
		std::cin >> x >> y >> z;
		ans -= delta(a[x]);
		a[x] += z;
		ans += delta(a[x]);
		if (y != n) { ans -= delta(a[y + 1]); a[y + 1] -= z; ans += delta(a[y + 1]); }
		std::cout << ans << "\n";
	}
	return 0;
}
