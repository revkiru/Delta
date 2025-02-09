#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	a[1] = a[n] = a[n >> 1] = 1;
	int cnt = 2;
	for (int i = 1; i <= n; i++) {
		if (!a[i])
			a[i] = cnt++;
	}
	for (int i = 1; i <= n; i++)
		std::cout << a[i] << " ";
	std::cout << "\n";
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
