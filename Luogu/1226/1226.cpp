#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
T expow(T a, T b, const T P) {
	T res = 1;;
	for (; b; b >>= 1) {
		if (b & 1)
			res = 1ll * res * a % P;
		a = 1ll * a * a % P;
	}
	return res;
}

void solve() {
	i64 a, b, p;
	std::cin >> a >> b >> p;
	std::cout << a << "^" << b << " mod " << p << "=" << expow<i64>(a, b, p) << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	solve();
	return 0;
}
