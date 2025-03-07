#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1007;
constexpr int inf = 1e9;

int n, m, ans;
int h[N][N], l[N][N], r[N][N];
char a[N][N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			std::cin >> a[i][j];
			h[i][j] = 1;
			l[i][j] = r[i][j] = j;
		}
		for (int j = 2; j <= m; j++) {
			if (a[i][j] == 'F' && a[i][j - 1] == 'F')
				l[i][j] = l[i][j - 1];
		}
		for (int j = m - 1; j > 0; j--) {
			if (a[i][j] == 'F' && a[i][j + 1] == 'F')
				r[i][j] = r[i][j + 1];
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (i > 1 && a[i][j] == 'F') {
				if (a[i - 1][j] == 'F') {
					h[i][j] = h[i - 1][j] + 1;
					if (l[i - 1][j] > l[i][j])
						l[i][j] = l[i - 1][j];
					if (r[i - 1][j] < r[i][j])
						r[i][j] = r[i - 1][j];
				}
				if ((r[i][j] - l[i][j] + 1) * h[i][j] > ans)
					ans = (r[i][j] - l[i][j] + 1) * h[i][j];
			}
		}
	}
	std::cout << ans * 3 << "\n";
	return 0;
}
