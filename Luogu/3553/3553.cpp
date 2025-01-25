#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<int> t(m + 1), u(m + 1), v(m + 1);
	for (int i = 1; i <= m; i++) {
		std::cin >> t[i] >> u[i] >> v[i];
	}

	const int inf = 1e9;
	auto check = [&](int x) -> bool {
		std::vector<int> mx(n + 1, -inf), mn(n + 1, inf);
		std::vector<int> tot(m + 1, 0), st(m + 1, 0), en(m + 1, 0);
		for (int i = 1; i <= x; i++) {
			mn[u[i]] = std::min(mn[u[i]], t[i]);
			mx[u[i]] = std::max(mx[u[i]], t[i]);
			if (tot[t[i]] && tot[t[i]] != v[i] + 1)
				return 0;
			tot[t[i]] = v[i] + 1;
		}
		for (int i = 1; i <= n; i++) {
			if (mx[i] != -inf) {
				st[mn[i]]++;
				en[mx[i]]++;
			}
		}
		int tal = 0, now = 0, dne = 0, nir = 0;
		for (int i = 1; i <= m; i++) {
			if (tot[i]) {
				now += st[i];
				if (now > tot[i])
					return 0;
				if (st[i] < nir)
					nir -= st[i];
				else {
					tal += st[i] - nir;
					nir = 0;
				}
				if (now + nir + dne < tot[i]) {
					tal += tot[i] - now - nir - dne;
					nir = tot[i] - now - dne;
				} else {
					if (now + nir > tot[i]) {
						nir = tot[i] - now;
						dne = 0;
					} else {
						dne = tot[i] - now - nir;
					}
				}
				now -= en[i];
				dne += en[i];
			}
		}
		if (tal > n)
			return 0;
		return 1;
	};

	int l = 1, r = m + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			l = mid + 1;
		} else
			r = mid;
	}
	std::cout << l - 1 << "\n";
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
