#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2007;

int n;
i64 f[N][N];

struct node {
	int a, b;
} arr[N];

bool cmp(const node &x, const node &y) {
	return x.a > y.a;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> arr[i].a >> arr[i].b;
	}
	std::sort(arr + 1, arr + n + 1, cmp);

	for (int i = 0; i <= n; i++)
		f[0][i] = f[i][n + 1] = -1e9;
	f[0][1] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j <= n; j++) {
			f[i][j] = std::max(f[i - 1][j], f[i - 1][std::max(j - arr[i].a, 0) + 1] + arr[i].b);
		}
	}
	i64 ans = -1e9;
	for (int i = 0; i <= n; i++)
		ans = std::max(ans, f[n][i]);
	std::cout << ans << "\n";
	return 0;
}
