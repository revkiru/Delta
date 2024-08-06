#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e7 + 7;
constexpr int P = 1e9 + 7;

int t0t, pri[N], vis[N], phi[N];
i64 phiSum[N];

void init(const int n) {
	phiSum[1] = phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			pri[++t0t] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; i * pri[j] <= n && j <= t0t; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			} else {
				phi[i * pri[j]] = phi[i] * phi[pri[j]];
			}
		}
	}
}

int n;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	init(n);
	for (int i = 1; i <= n; i++)
		phiSum[i] = (phiSum[i - 1] + phi[i]) % P;
	i64 ans = 0;
	for (i64 i = 1; i <= n; i++)
		ans = (ans + i * i * (2 * phiSum[n / i] - 1) % P) % P;
	std::cout << ans << "\n";
	return 0;
}
