#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e8 + 7;

int n, m, q;
int v[N], pri[N];

void primes(const int n) {
	for (int i = 2; i <= n; i++) {
		if (v[i] == 0) { v[i] = i; pri[++m] = i; }
		for (int j = 1; j <= m; j++) {
			if (pri[j] > v[i] || pri[j] > n / i)
				break;
			v[i * pri[j]] = pri[j];
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q;
	primes(n);
	while (q--) {
		int k;
		std::cin >> k;
		std::cout << pri[k] << "\n";
	}
	return 0;
}
