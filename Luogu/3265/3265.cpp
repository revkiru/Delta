#include <bits/stdc++.h>

using i64 = long long;
using l64 = long double;

constexpr int N = 507;
constexpr l64 eps = 1e-8;

int n, m, dim, ans;
int c[N];
l64 a[N][N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			l64 x;
			std::cin >> x;
			a[i][j] = x;
		}
	}
	for (int i = 1; i <= n; i++) {
		l64 x;
		std::cin >> x;
		c[i] = x;
	}

	int dim = 0;
	for (int i = 1; i <= m; i++) {
		int u = 0;
		for (int j = dim + 1; j <= n; j++) {
			if (std::fabs(a[j][i]) > eps && (u == 0 || c[j] < c[u]))
				u = j;
		}
		if (u == 0) {
			continue;
		}
		dim++;
		ans += c[u];
		for (int j = 1; j <= m; j++)
			std::swap(a[u][j], a[dim][j]);
		std::swap(c[u], c[dim]);
		for (int j = 1; j <= n; j++) {
			if (dim != j && std::abs(a[j][i]) > eps) {
				l64 rat = a[j][i] / a[dim][i];
				for (int k = i; k <= m; k++)
					a[j][k] -= a[dim][k] * rat;
			}
		}
	}
	std::cout << dim << " " << ans << "\n";
	return 0;
}
