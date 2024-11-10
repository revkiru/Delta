#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	std::vector<int> pre(n + 1);
	int cur = 0;
	for (int i = 1; i <= n; i++) {
		if (cur < a[i])
			cur++;
		else if (cur > a[i])
			cur--;
		pre[i] = std::max(pre[i - 1], cur);
	}
	auto check = [&](int k) {
		int g = k;
		for (int i = n; i >= 1; i--) {
			if (pre[i - 1] >= g)
				return 1;
			if (a[i] < g)
				g++;
			else
				g--;
		}
		return 0;
	};
	int l = 0, r = n + 1;
	while (l < r) {
		int mid = (l + r + 1) >> 1;
		if (check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	std::cout << l << "\n";
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
