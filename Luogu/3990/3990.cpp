#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int P = 30011;

int n, m;

struct Matrix {
	i64 a[N][N];

	void clear() { memset(a, 0, sizeof(a)); }

	Matrix operator * (const Matrix &rhs) const {
		Matrix ret;
		ret.clear();
		for (int i = 1; i <= (n << 1); i++) {
			for (int j = 1; j <= (n << 1); j++)
				for (int k = 1; k <= (n << 1); k++)
					ret.a[i][j] = (ret.a[i][j] + (a[i][k] * rhs.a[k][j]) % P) % P;
		}
		return ret;
	}
} b, c, d;

void build() {
	for (int i = 1; i <= n; i++) {
		if (i != 1)
			b.a[i][i - 1] = 1;
		b.a[i][i] = 1;
		if (i != n)
			b.a[i][i + 1] = 1;
	}
	for (int i = 1; i <= n; i++)
		b.a[i][i + n] = 1;
	for (int i = 1; i <= n; i++)
		b.a[i + n][i] = 1;
}

void expow() {
	for (; m; m >>= 1) {
		if (m & 1)
			c = c * b;
		b = b * b;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	build();
	d = b;
	m -= 2;
	for (int i = 1; i <= (n << 1); i++)
		c.a[i][i] = 1;
	expow();
	int ans = -c.a[1][n << 1];
	c = c * d;
	ans += c.a[1][n];
	std::cout << (ans + P) % P << "\n";
	return 0;
}
