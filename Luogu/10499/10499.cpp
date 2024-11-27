#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;

int n, ans;
int a[N];

void solve() {
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int i = 1, j; i <= n; i++) {
		std::cin >> j;
		a[i] ^= j;
		// = a[i][i] = 1
		a[i] |= (1 << i);
	}
	int x, y;
	while (std::cin >> x >> y && x && y) {
		// = a[y][x] = 1
		a[y] |= (1 << x);
		// std::cout << a[y] << "!!!\n";
	}
	
	ans = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = i + 1; j <= n; j++) {
			if (a[j] > a[i])
				std::swap(a[i], a[j]);
		}
		if (a[i] == 0) { ans = 1 << (n - i + 1); break; }
		if (a[i] == 1) { ans = 0; break; }
		for (int k = n; k; k--) {
			if ((a[i] >> k) & 1) {
				for (int j = 1; j <= n; j++)
					if (i != j && ((a[j] >> k) & 1))
						a[j] ^= a[i];
				break;
			}
		}
	}
	if (!ans) { std::cout << "Oh,it's impossible~!!\n"; }
	else { std::cout << ans << "\n"; }
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
