#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int P = 1e9 + 7;

int n;
i64 k;

struct Matrix {
	i64 a[N][N];

	void clear() { memset(a, 0, sizeof(a)); }

	Matrix operator * (const Matrix &rhs) const {
		Matrix ret;
		ret.clear();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				for (int k = 1; k <= n; k++)
					ret.a[i][j] = (ret.a[i][j] + (a[i][k] * rhs.a[k][j]) % P) % P;
		}
		return ret;
	}
} A;

Matrix expow(Matrix a, i64 b) {
	Matrix ret;
	ret.clear();
	for (int i = 1; i <= n; i++)
		ret.a[i][i] = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a;
		a = a * a;
	}
	return ret;
}

void solve() {
	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			std::cin >> A.a[i][j];
	}
	A = expow(A, k);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			std::cout << A.a[i][j] << " ";
		std::cout << "\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
