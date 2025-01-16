#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;

void solve() {
	u64 a, b;
	std::cin >> a >> b;
	if (a == b) {
		std::cout << "1\n";
		return;
	}

	u64 ans = b - a + 1;
	u64 U = (1ull << (sizeof(u64) * 8 - __builtin_clzll(a ^ b) - 1)) - 1;
	a &= U, b &= U;

	u64 r = sizeof(u64) * 8 - __builtin_clzll(b);
	if (__builtin_clzll(a) >= __builtin_clzll(b))
		ans += U - b;
	else
		ans += U - a + (1ull << r) - b;
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}

/* O(1) 的大分讨 */
