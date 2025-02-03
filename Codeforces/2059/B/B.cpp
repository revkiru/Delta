#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n, k;
	std::cin >> n >> k;
	k /= 2;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	if (n == k * 2) {
		for (int i = 2; i <= n; i += 2) {
			if (a[i] != (i + 1) / 2) {
				std::cout << (i + 1) / 2 << "\n";
				return;
			}
		}
		std::cout << k + 1 << "\n";
	} else {
		for (int i = 2; i <= n - 2 * k + 2; i++) {
			if (a[i] != 1) {
				std::cout << "1\n";
				return;
			}
		}
		std::cout << "2\n";
	}
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
