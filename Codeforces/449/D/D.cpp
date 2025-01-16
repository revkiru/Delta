#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;
constexpr int P = 1e9 + 7;

int n, s;
i64 f[N];

template <typename T>
T expow(T a, T b) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % P;
		a = a * a % P;
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		f[x]++;
	}

	s = (1 << 20) - 1;
	for (int i = 0; i < 20; i++) {
		for (int j = s; j >= 0; j--) {
			if ((j & (1 << i)) == 0)
				f[j] = (f[j] + f[j | (1 << i)] % P + P) % P;
		}
	}
	for (int i = 0; i < s; i++)
		f[i] = expow<i64>(2, f[i]) - 1;
	for (int i = 0; i < 20; i++) {
		for (int j = s; j >= 0; j--) {
			if ((j & (1 << i)) == 0)
				f[j] = (f[j] - f[j | (1 << i)] % P + P) % P;
		}
	}
	std::cout << f[0] << "\n";
	return 0;
}
