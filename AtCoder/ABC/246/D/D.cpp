#include <bits/stdc++.h>

#define int long long

constexpr int inf = 1e18;
constexpr int R = 1e6 + 1;

int n, ans = inf;

int calc(int a, int b) {
	return a * a * a + b * b * b + a * a * b + a * b * b;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	int l = 0, r = R;
	while (l <= R && r >= 0) {
		if (calc(l, r) < n)
			l++;
		else {
			ans = std::min(ans, calc(l, r));
			r--;
		}
	}
	std::cout << ans << "\n";
	return 0;
}
