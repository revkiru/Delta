#include <bits/stdc++.h>

using i64 = long long;

i64 n, k, ans;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	ans = n * k;
	for (int x = 1, gx; x <= n; x = gx + 1) {
		gx = k / x ? std::min(k / (k / x), n) : n;
		ans -= (k / x) * (x + gx) * (gx - x + 1) / 2;
	}
	std::cout << ans << "\n";
	return 0;
}
