#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e7 + 7;
constexpr int P = 998244353;

int n, k;
int fac[N], inv[N];
int f[N], g[N];

template <typename T>
T expow(T a, T b) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % P;
		a = 1ll * a * a % P;
	}
	return ret;
}

void modAdd(int &x, int y) { if ((x += y) >= P) x -= P; }

void modMns(int &x, int y) { if ((x -= y) < 0) x += P; }

void init() {
	const int R = 10000000;
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= R; i++)
		fac[i] = 1ll * fac[i - 1] * i % P;
	inv[R - 1] = expow(fac[R - 1], P - 2);
	for (int i = R - 2; i; i--)
		inv[i] = 1ll * inv[i + 1] * (i + 1) % P;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	init();

	f[0] = g[0] = 1;
	for (int i = 1; i <= n; i++) {
		g[i] = f[i] = g[i - 1];
		if (i > k)
			modMns(f[i], g[i - k - 1]);
		f[i] = 1ll * f[i] * fac[i - 1] % P;
		modAdd(g[i], 1ll * f[i] * inv[i] % P);

	}
	std::cout << f[n] << "\n";
	return 0;
}
