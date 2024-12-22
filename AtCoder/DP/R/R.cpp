#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 107;
constexpr int P = 1e9 + 7;

i64 n, k, ans;
i64 dp[N][N];

struct Matrix {
	i64 a[N][N];

	Matrix operator * (const Matrix &rhs) const {
		Matrix c;
		memset(c.a, 0, sizeof(c.a));
		for (int i = 1; i <= n; i++) {
			for (int k = 1; k <= n; k++) {
				for (int j = 1; j <= n; j++) {
					c.a[i][j] += a[i][k] * rhs.a[k][j];
					c.a[i][j] %= P;
				}
			}
		}
		return c;
	}
} dis, res;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			std::cin >> dis.a[i][j];
		res.a[i][i] = 1;
	}
	for (; k; k >>= 1, dis = dis * dis)
		if (k & 1)
			res = res * dis;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			ans += res.a[i][j];
			ans %= P;
		}
	}
	std::cout << ans << "\n";
	return 0;
}
