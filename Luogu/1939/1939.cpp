#include <bits/stdc++.h>

using i64 = long long;

constexpr int P = 1e9 + 7;

int n;

struct Matrix {
	int n, m;
	i64 a[5][5];

	void init(const int _n, const int _m) { n = _n; m = _m; }

	void clear() { n = m = 0; memset(a, 0, sizeof(a)); }

	Matrix operator * (const Matrix &rhs) const {
		Matrix ret;
		ret.clear();
		ret.init(n, rhs.m);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= rhs.m; j++)
				for (int k = 1; k <= m; k++)
					ret.a[i][j] = (ret.a[i][j] + (a[i][k] * rhs.a[k][j]) % P) % P;
		}
		return ret;
	}
} A, p;

Matrix expow(Matrix a, i64 b) {
	Matrix ret;
	ret.clear();
	ret.init(a.n, a.m);
	for (int i = 1; i <= ret.n; i++)
		ret.a[i][i] = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a;
		a = a * a;
	}
	return ret;
}

void solve() {
	A.clear();
	A.init(1, 3);
	A.a[1][1] = A.a[1][2] = A.a[1][3] = 1;

	std::cin >> n;
	if (n < 3) { std::cout << "1\n"; return; }
	A = A * (expow(p, n - 3));
	std::cout << A.a[1][3] << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;

	p.init(3, 3);
	p.a[1][3] = p.a[2][1] = p.a[3][2] = p.a[3][3] = 1;

	while (t--) {
		solve();
	}
	return 0;
}
