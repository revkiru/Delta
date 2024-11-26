#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 20;
constexpr int P = 9901;

int a, b, m, ans = 1;
int p[N], c[N];

template <typename T>
T expow(T a, T b, const T P) {
	T res = 1 % P;
	for (; b; b >>= 1) {
		if (b & 1) res = 1ll * res * a % P;
		a = 1ll * a * a % P;
	}
	return res;
}

void div(int n) {
	m = 0;
	for (int i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			p[++m] = i; c[m] = 0;
			while (n % i == 0) {
				n /= i;
				c[m]++;
			}
		}
	}
	if (n > 1) { p[++m] = n; c[m] = 1; }
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> a >> b;
	div(a);
	for (int i = 1; i <= m; i++) {
		if ((p[i] - 1) % P == 0) {	// 无逆元
			ans = (1ll * b * c[i] + 1) % P * ans % P;
			continue;
		}
		int x = expow((i64) p[i], 1ll * b * c[i] + 1, (i64) P);
		x = (x - 1 + P) % P;
		int y = p[i] - 1;
		y = expow((i64) y, (i64) P - 2, (i64) P);
		ans = 1ll * ans * x % P * y % P;
	}
	std::cout << ans << "\n";
	return 0;
}
