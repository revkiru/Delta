#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n, m, k, t;
	std::cin >> m >> n >> k >> t;
	std::vector<int> a(m + 1);
	for (int i = 1; i <= m; i++)
		std::cin >> a[i];
	std::vector<int> l(k + 1), r(k + 1), d(k + 1);
	for (int i = 1; i <= k; i++)
		std::cin >> l[i] >> r[i] >> d[i];
	std::sort(a.begin() + 1, a.end(), std::greater<int>());

	auto check = [&](int x) -> bool {
		int mn = *std::min_element(a.begin() + 1, a.begin() + x + 1);
		std::vector<std::pair<int, int>> seg;
		for (int i = 1; i <= k; i++)
			if (d[i] > mn)
				seg.push_back({l[i], r[i]});
		int ret = 0;
		std::sort(seg.begin(), seg.end());
		int lb = 0;
		for (auto i : seg) {
			if (i.first <= lb) {
				ret += std::max(0, i.second - lb);
				lb = std::max(i.second, lb);
			} else {
				ret += i.second - i.first + 1;
				lb = i.second;
			}
		}
		ret = 2 * ret + n + 1;
		return ret <= t;
	};

	int _l = 0, _r = m + 1;
	while (_l + 1 < _r) {
		int mid = (_l + _r) >> 1;
		if (check(mid))
			_l = mid;
		else
			_r = mid;
	}
	std::cout << _l << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
