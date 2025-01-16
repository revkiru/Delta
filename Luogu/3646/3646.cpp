#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e3 + 7;
constexpr int M = 107;
constexpr int R = 40;

int n, l, r;
i64 ans;
int a[N];

namespace Sol1 {
	bool f[M][M];

	bool check(int p) {
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				i64 res = a[i];
				for (int k = i - 1; ~k; k--) {
					f[i][j] |= f[k][j - 1] && ((!((res >> p) & 1)) && ((((res >> p) << p) | ans) == ans));
					res += a[k];
				}
			}
		}
		for (int i = l; i <= r; i++)
			if (f[n][i])
				return 1;
		return 0;
	}
}

namespace Sol2 {
	int f[N];

	bool check(int p) {
		memset(f, 0x3f, sizeof(f));
		f[0] = 0;
		for (int i = 1; i <= n; i++) {
			i64 res = a[i];
			for (int j = i - 1; ~j; j--) {
				if ((!((res >> p) & 1)) && ((((res >> p) << p) | ans) == ans)) {
					f[i] = std::min(f[i], f[j] + 1);
				}
				res += a[j];
			}
		}
		return f[n] <= r;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> l >> r;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	for (int i = 40; ~i; i--) {
		if (!(n <= 100 ? Sol1::check(i) : Sol2::check(i))) {
			ans |= (1ll << i);
			// std::cout << i << ", ";
		}
	}
	std::cout << ans << "\n";
	return 0;
}
