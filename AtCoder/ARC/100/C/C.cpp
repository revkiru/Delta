#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1 << 20;

int n, mxn, ans;
std::pair<int, int> f[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 0, x; i < (1 << n); i++) {
		std::cin >> x;
		f[i].first = x;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (1 << n); j++) {
			if ((1 << i) & j) {
				int mx1 = f[j].first, mx2 = f[j].second;
				int mx3 = f[j ^ (1 << i)].first, mx4 = f[j ^ (1 << i)].second;
				if (mx3 > mx1) {
					mx2 = std::max(mx1, mx4);
					mx1 = mx3;
				} else {
					mx2 = std::max(mx2, mx3);
				}
				f[j].first = mx1;
				f[j].second = mx2;
			}
		}
	}
	for (int i = 1; i < (1 << n); i++) {
		ans = std::max(ans, f[i].first + f[i].second);
		std::cout << ans << "\n";
	}
	return 0;
}
