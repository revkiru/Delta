#include <bits/stdc++.h>

using i64 = long long;

int f = 1;
i64 x, y, m, n, l, d, k, z;

template <typename T>
T exgcd(T a, T b, T &x, T &y) {
	if (b == 0) { x = 1, y = 0; return a; }
	T d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> x >> y >> m >> n >> l;
	if (m < n) { std::swap(n, m); f *= -1; }
	d = exgcd(m - n, l, k, z);	// 求解 k * (m - n) + zl = gcd(m - n, l)
	if ((y - x) % d != 0) {
		std::cout << "Impossible\n";
		exit(0);
	}
	k = f * k * (y - x) / d;	// 求解 k * (m - n) + zl = y - x
	k = (k % (l / d) + (l / d)) % (l / d);	// 最小正数 k
	std::cout << k << "\n";
	return 0;
}
