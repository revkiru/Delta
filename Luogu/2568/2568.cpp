#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e7 + 7;

int n, t0t;
int phi[N], p[N];
i64 ans, sphi[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	phi[1] = sphi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!phi[i]) {
			p[++t0t] = i;
			phi[i] = i - 1;
		}
		sphi[i] = sphi[i - 1] + phi[i];
		for (int j = 1; j <= t0t && i * p[j] <= n; j++) {
			if (i % p[j] == 0) {
				phi[i * p[j]] = phi[i] * p[j];
			} else {
				phi[i * p[j]] = phi[i] * (p[j] - 1);
			}
		}
	}

	for (int i = 1; i <= t0t; i++)	// ans += 2 * (phi(1) + phi(2) + .. + phi(n / p)) - 1
		ans += sphi[n / p[i]] * 2 - 1;
	std::cout << ans << "\n";
	return 0;
}
