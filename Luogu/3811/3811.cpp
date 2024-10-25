#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e6 + 7;

int n, p;
int inv[N];

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) { sum = 1ll * sum * 10 + (ch - '0'); }
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) { write(x / 10); }
	putchar(x % 10 + '0');
}

template <typename T>
T expow(T a, T b, const T P) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = 1ll * ret * a % P;
		a = 1ll * a * a % P;
	}
	return ret;
}

int main() {
	n = read<int>(), p = read<int>();
	inv[1] = 1;
	puts("1");
	for (int i = 2; i <= n; i++) {
		inv[i] = (i64) (p - p / i) * inv[p % i] % p;
		write<int>(inv[i]);
		puts("");
	}
	return 0;
}
