#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 807;

int n, k, lim;
int a[N][N], b[N][N];

bool check(int x) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			b[i][j] = a[i][j] > x;
			b[i][j] = b[i][j - 1] + b[i - 1][j] - b[i - 1][j - 1] + b[i][j];
		}
	}
	for (int i = 1; i <= n - k + 1; i++) {
		for (int j = 1; j <= n - k + 1; j++) {
			int c = b[i - 1][j - 1] + b[i + k - 1][j + k - 1] - b[i - 1][j + k - 1] - b[i + k - 1][j - 1];
			if (c <= lim)
				return 1;
		}
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	lim = k * k / 2;
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			std::cin >> a[i][j];
			r = std::max(r, a[i][j]);
		}
	}

	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}

	std::cout << r << "\n";
	return 0;
}
