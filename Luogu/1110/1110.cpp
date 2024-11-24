#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int inf = 1e9;

int n, m, ans = inf;
int bg[N], ed[N];

std::multiset<int> alt, dlt;

void update(int i) {
	auto it = alt.lower_bound(i);
	int _i = *it - i;
	--it;
	_i = std::min(_i, i - *it);
	ans = std::min(ans, _i);
	alt.insert(i);
}

void replace(int i, int x) {
	dlt.insert(std::abs(x - ed[i]));
	if (i != n) {
		dlt.erase(dlt.find(std::abs(bg[i + 1] - ed[i])));
		dlt.insert(std::abs(bg[i + 1] - x));
	}
	ed[i] = x;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> bg[i];
		ed[i] = bg[i];
	}
	alt.insert(inf), alt.insert(-inf);
	for (int i = 1; i < n; i++) {
		dlt.insert(std::abs(bg[i + 1] - ed[i]));
	}
	for (int i = 1; i <= n; i++) {
		update(bg[i]);
	}
	while (m--) {
		std::string opt;
		int p, k;
		std::cin >> opt;
		if (opt == "INSERT") {
			std::cin >> p >> k;
			update(k);
			replace(p, k);
		}
		if (opt == "MIN_SORT_GAP") {
			std::cout << ans << "\n";
		}
		if (opt == "MIN_GAP") {
			std::cout << *dlt.begin() << "\n";
		}
	}
	return 0;
}
