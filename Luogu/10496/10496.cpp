#include <bits/stdc++.h>

#define int long long

using i128 = __int128;

int T, L;

int expow(i128 a, i128 b, const i128 P) {
	i128 res = 1 % P;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a % P;
		a = a * a % P;
	}
	return res;
}

int phi(int n) {
	int ret = n;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			ret = ret / i * (i - 1);
			while (n % i == 0)
				n /= i;
		}
	}
	if (n > 1) {
		ret = ret / n * (n - 1);
	}
	return ret;
}

void solve() {
	std::cout << "Case " << ++T << ": ";
	L = 9 * L / std::__gcd(L, 8ll);
	if (std::__gcd(L, 10ll) != 1) {
		std::cout << "0\n";
		return;
	}
	int x = phi(L);
	std::vector<int> vec;
	for (int i = 1; i * i <= x; i++) {
		if (x % i == 0) {
			vec.push_back(i);
			if (x / i != i)
				vec.push_back(x / i);
		}
	}
	std::sort(vec.begin(), vec.end());
	for (auto i : vec) {
		if (expow(10ll, i, L) == 1) {
			std::cout << i << "\n";
			return;
		}
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	while (std::cin >> L && L) {
		solve();
	}
	return 0;
}
