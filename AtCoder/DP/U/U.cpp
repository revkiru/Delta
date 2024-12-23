#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 16;

int n;
i64 a[N][N], f[1 << N];

i64 dp(int i) {
	if (~f[i]) { return f[i]; }
	f[i] = 0;
	for (int j = 0; j < n; j++) {
		for (int k = j + 1; k < n; k++)
			if ((i >> j) & 1 && (i >> k) & 1)
				f[i] += a[j][k];
	}
	for (int j = i; j = (j - 1) & i;)
		f[i] = std::max(f[i], dp(j) + dp(j ^ i));
	return f[i];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			std::cin >> a[i][j];
	memset(f, -1, sizeof(f));
	std::cout << dp((1 << n) - 1) << "\n";
	return 0;
}
