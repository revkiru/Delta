#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::string s;
	std::cin >> s;
	s = '$' + s;

	i64 sum = 0;
	std::vector<i64> a(n + 1);
	for (int i = 1; i <= n; i++) {
		a[i] = s[i] - '0';
		sum += 1ll * i * a[i];
	}
	std::vector<i64> ans(n << 1 | 1);
	for (int i = 0; i < n; i++) {
		ans[i] = sum;
		sum -= 1ll * (n - i) * a[n - i];
	}
	// std::cout << sum << "\n";
	int len = 0;
	for (int i = 0; i < (n << 1); i++) {
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
		if (ans[i])
			len = i;
	}
	for (int i = len; i >= 0; i--) {
		std::cout << ans[i];
	}
	std::cout << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
