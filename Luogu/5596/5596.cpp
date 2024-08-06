#include <bits/stdc++.h>

#define int long long

int a, b, ans;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> a >> b;
	if (a * a == 4 * b) { std::cout << "inf\n"; exit(0); }
	int x = 1, d = std::sqrt(b);
	if (d * d == b) ans++;
	while (1) {
		int A = 2 * x - a, B = b - x * x;
		if (((A > 0 && B > 0) || (A < 0 && B < 0)) && !(B % A)) ans++;
		if (A > 0 && B < 0) break;
		x++;
	}
	std::cout << ans << "\n";
	return 0;
}
