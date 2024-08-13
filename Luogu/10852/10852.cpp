#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n, m;
	std::cin >> n >> m;
	std::vector<std::pair<i64, i64>> v;
	for (int i = 1; i <= m; i++) {
		int x, y;
		std::cin >> x >> y;
		v.push_back({x, y});
	}
	std::sort(v.begin(), v.end());
	int tf = -1;
	for (size_t i = 0; i + 1 < v.size(); i++) {
		i64 dlt = v[i + 1].first - v[i].first;
		i64 val = v[i + 1].second - v[i].second;
		if (val % dlt) { std::cout << "No\n"; return; }
		int glt = val / dlt;
		if (!i) tf = glt;
		else if (tf != glt) { std::cout << "No\n"; return; }
	}
	std::cout << "Yes\n";
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
