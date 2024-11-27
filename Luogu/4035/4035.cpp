#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 27;
constexpr double eps = 1e-8;

int n;
double a[N][N], b[N], c[N][N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n + 1; i++) {
		for (int j = 1; j <= n; j++) {
			std::cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			c[i][j] = 2 * (a[i][j] - a[i + 1][j]);
			b[i] += a[i][j] * a[i][j] - a[i + 1][j] * a[i + 1][j];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			if (std::fabs(c[j][i]) > eps) {
				for (int k = 1; k <= n; k++)
					std::swap(c[i][k], c[j][k]);
				std::swap(b[i], b[j]);
			}
		}
		for (int j = 1; j <= n; j++) {
			if (i == j)
				continue;
			double rat = c[j][i] / c[i][i];
			for (int k = i; k <= n; k++)
				c[j][k] -= c[i][k] * rat;
			b[j] -= b[i] * rat;
		}
	}
	for (int i = 1; i <= n; i++)
		std::cout << std::fixed << std::setprecision(3) << b[i] / c[i][i] << " ";
	std::cout << "\n";
	return 0;
}
