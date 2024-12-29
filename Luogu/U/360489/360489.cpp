#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int a[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i] ^= a[i - 1];
	}

	i64 ans = 0;
	// 2^21
	for (int k = 0; k < 21; k++) {
		i64 cot = 0;
		for (int i = 0; i <= n; i++)
			if (a[i] >> k & 1)
				cot++;
		ans += cot * (n + 1 - cot) * (1 << k);
	}
	std::cout << ans << "\n";
	return 0;
}
