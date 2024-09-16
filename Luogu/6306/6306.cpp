#include <bits/stdc++.h>

#define int long long

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

constexpr int N = 57;
constexpr int K = 100;

int n, k, t0t, base;
int s[N][K];

template <typename T>
T expow(T a, T b) {
	T res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = 1ll * res * a;
		a = 1ll * a * a;
	}
	return res;
}

signed main() {
    n = read<int>(), k = read<int>();
    for (int i = 1, x; i <= n; i++) {
        x = read<int>();
        for (int j = 0; x != 0; j++) {
            if (x % K != 0)
                s[j][x % K]++;
            x /= K;
            base = std::max(base, j);
        }
    }
    for (int i = 0; i <= base; i++) {
        for (int j = 0; j <= 99; j++) {
            s[i][j] %= k;
            if (s[i][j] != 1)
                continue;
            t0t += (expow(K, i) * j);
        }
    }
    write<int>(t0t);
    puts("");
    return 0;
}
