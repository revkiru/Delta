#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n, P;
int lg2[N], fac[N], inv[N], f[N];

template <typename T>
T expow(T a, T b) {
	T res = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			res = 1ll * res * a % P;
		a = 1ll * a * a % P;
	}
	return res;
}

void init() {
	fac[0] = 1, lg2[0] = -1;
	for (int i = 1; i <= n; i++) {
		fac[i] = 1ll * fac[i - 1] * i % P;
		lg2[i] = lg2[i >> 1] + 1;
	}
	const int R = std::min(P - 1, n);
	inv[R] = expow(fac[R], P - 2);
	for (int i = R - 1; ~i; i--) {
		inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
	}
}

int C(int n, int m) {
	if (!m) return 1;
	int u = C(n / P, m / P);
	int _n = n % P, _m = m % P, t = 0;
	if (_n < _m) t = 0;
	else t = (1ll * fac[_n] * inv[_m] % P) * inv[_n - _m] % P;
	return 1ll * u * t % P;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> P;
	init();

	f[1] = f[2] = 1;
	f[3] = 2;
	int l = 1, r = 1;
	for (int i = 4; i <= n; i++) {
		if (i - (1 << lg2[i]) + 1 <= (1 << (lg2[i] - 1))) l++;
		else r++;
		f[i] = 1ll * (1ll * C(i - 1, l) * f[l] % P) * f[r] % P;
	}
	std::cout << f[n] << "\n";
	return 0;
}
