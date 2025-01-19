#include <bits/stdc++.h>

#define int long long

constexpr int N = 57;
constexpr int L = 1e4 + 7;
constexpr int P = 1e9 + 7;

int n, l, ans;
int r[N], fac[L], inv[L];
int f[N][N][L];

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

void init() {
	fac[0] = 1;
	for (int i = 1; i <= 10000; i++) {
		fac[i] = fac[i - 1] * i % P;
		inv[i] = expow(fac[i], P - 2);
	}
}

int C(int n, int m) {
	if (n < m) return 0;
	if (n == m) return 1;
	return fac[n] * inv[m] % P * inv[n - m] % P;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();

	std::cin >> n >> l;
	for (int i = 1; i <= n; i++)
		std::cin >> r[i];

	std::sort(r + 1, r + n + 1);
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i; j++) {
			for (int k = 1; k <= l; k++) {
				f[i][j][k] = f[i - 1][j - 1][k - 1];
				if (k >= r[i]) { f[i][j][k] += f[i - 1][j][k - r[i]] * j % P * 2 % P; f[i][j][k] %= P; }
				if (k >= r[i] * 2 - 1) { f[i][j][k] += f[i - 1][j + 1][k - r[i] * 2 + 1] * (j + 1) % P * j % P; f[i][j][k] %= P; }
			}
		}
	}

	for (int i = 1; i <= l; i++) {
		ans += f[n][1][i] * C(l + n - i, n);
		ans %= P;
	}
	std::cout << ans << "\n";
	return 0;
}
