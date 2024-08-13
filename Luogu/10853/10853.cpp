#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1), b(n + 1);
	std::map<int, int> cot;

	int cnt0 = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		if (a[i]) {
			b[i] = 31 - __builtin_clz((unsigned) a[i]);
			++cot[b[i]];
		} else ++cnt0;
	}

	i64 ans = 1ll * n * cnt0;
	for (int i = 1; i <= n; i++) {
		if (a[i]) {
			for (int x = 0; x < b[i]; x++)
				if ((a[i] >> x) & 1)
					ans += cot[x];
		}
	}

	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
