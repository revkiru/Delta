#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e4 + 7;
const int a[] = {2, 3, 4679, 35617};

int n, g, ans, P = 999911658;
int p[N], b[5];

template <typename T>
T expow(T a, T b) {
	T res = 1 % P;
	for (; b; b >>= 1) {
		if (b & 1) res = 1ll * res * a % P;
		a = 1ll * a * a % P;
	}
	return res;
}

template <typename T>
void exgcd(T a, T b, T &x, T &y) {
	if (b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

int inv(int a, int p) {
	int x, y;
	exgcd(a, p, x, y);
	return (x % p + p) % p;
}

int calc(int x, const int mod) {
	int ret = 1, y, a, b;
	for (y = n; x; x /= mod, y /= mod) {
		a = x % mod, b = y % mod;
		ret = (i64) ret * p[b] % mod * inv(p[a], mod) % mod * inv(b < a ? 0 : p[b - a], mod) % mod;
	}
	return ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> g;
	g %= P + 1;
	if (!g) { std::cout << "0\n"; exit(0); }
	
	p[0] = 1;
	for (int i = 1; i <= a[3]; i++) {
		p[i] = (i64) p[i - 1] * i % P;
	}
	for (int i = 1; i * i <= n; i++) {
		if (n % i == 0) {
			for (int j = 0; j < 4; j++) {
				b[j] = (b[j] + calc(i, a[j])) % a[j];
			}
			if (i * i != n) {
				for (int j = 0; j < 4; j++) {
					b[j] = (b[j] + calc(n / i, a[j])) % a[j];
				}
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		int x, y;
		exgcd(P / a[i], a[i], x, y);
		ans = (ans + (i64) x * (P / a[i]) % P * b[i]) % P;
	}
	ans = (ans + P) % P;
	P++;
	ans = expow(g, ans);
	std::cout << ans << "\n";
	return 0;
}
