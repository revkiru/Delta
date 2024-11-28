#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int miu[N], v[N];

void init() {
	for (int i = 1; i < N; i++) { miu[i] = 1; v[i] = 0; }
	for (int i = 2; i < N; i++) {
		if (v[i]) { continue; }
		miu[i] = -1;
		for (int j = i * 2; j < N; j += i) {
			v[j] = 1;
			if (j / i % i == 0) { miu[j] = 0; }
			else { miu[j] *= -1; }
		}
	}
	for (int i = 1; i < N; i++) { miu[i] += miu[i - 1]; }
}

void solve() {
	int a, b, k;
	std::cin >> a >> b >> k;
	a /= k, b /= k;
	if (a > b) { std::swap(a, b); }

	int ans = 0;
	for (int x = 1, gx; x <= a; x = gx + 1) {
		gx = std::min(a / (a / x), b / (b / x));
		ans += (miu[gx] - miu[x - 1]) * (a / x) * (b / x);
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();
	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
