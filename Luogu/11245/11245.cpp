#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

void solve() {
	u64 l, r, m, n;
	std::cin >> l >> r >> m >> n;
	if (!n || !m) {
		std::cout << "Yes\n";
		return;
	}
	if (l == 1) {
		std::cout << "No\n";
		return;
	}

	if (n > m) {
		std::swap(n, m);
	}
	u64 a = (n - 1) / (l - 1);
	u64 b = n - a * (l - 1);
	u64 c = a * (l + 1) + std::min(b - 1, a * (r - l));
	if (c <= m)
		std::cout << "Yes\n";
	else
		std::cout << "No\n";
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
