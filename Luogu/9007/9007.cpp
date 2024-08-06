#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e6 + 7;
constexpr int P = 998244353;

int t0t, ans = 1;
int val[N], pri[N], inv[N];
int f[N], num[N];

void init(const int n) {
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!val[i]) {
			pri[++t0t] = i;
			val[i] = i;
		}
		inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		for (int j = 1; j <= t0t && i <= n / pri[j]; j++) {
			val[i * pri[j]] = pri[j];
			if (i % pri[j] == 0)
				break;
		}
	}
}

void update(int x, int y) {
	while (x > 1) {
		int g = val[x];
		ans = 1ll * ans * inv[num[g] + 1] % P;
		num[g] += y;
		ans = 1ll * ans * (num[g] + 1) % P;
		x /= g;
	}
}

void solve() {
	int n;
	std::cin >> n;
	if (n == 1) { std::cout << "inf\n"; }
	else std::cout << f[n - 1] << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init(int(3e6 + 5));
	for (int i = 1; i <= 1e6 + 5; i++) {
		update(i, 2);
		f[i] = ans;
		update(i, -1);
	}

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
