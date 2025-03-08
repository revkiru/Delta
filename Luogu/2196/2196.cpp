#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 207;

int n, st, ans;
int a[N], f[N], p[N];
int G[N][N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}

	for (int i = 1, x; i < n; i++) {
		for (int j = i + 1; j <= n; j++) {
			std::cin >> x;
			if (x)
				G[i][j] = 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (G[j][i] && f[j] > f[i]) {
				f[i] = f[j];
				p[i] = j;
			}
		}
		f[i] += a[i];
		if (f[i] > ans) { ans = f[i]; st = i; }
	}

	std::function<void(int)> output = [&](int x) {
		if (!p[x]) { std::cout << x; return; }
		output(p[x]);
		std::cout << " " << x;
	};

	output(st);
	std::cout << "\n" << ans << "\n";
	return 0;
}
