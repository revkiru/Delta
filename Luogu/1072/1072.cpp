#include <bits/stdc++.h>

using i64 = long long;

bool judge(int i, int j) {
	return std::__gcd(i, j) == 1;
}

void solve() {
	int a0, a1, b0, b1;
	std::cin >> a0 >> a1 >> b0 >> b1;
	if (b1 % a1) {
		std::cout << "0\n";
		return;
	}
	int ans = 0, k = b1 / a1;
	for (int i = 1; i * i <= k; i++) {
		if (k % i == 0) {
			if (judge(i, a0 / a1) && judge(k / i, b1 / b0)) ans++;
			if (i * i != k && judge(k / i, a0 / a1) && judge(i, b1 / b0)) ans++;
		}
	}
	std::cout << ans << "\n";
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
