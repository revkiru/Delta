#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;

using i64 = long long;
using u32 = unsigned int;

constexpr int N = 1e6 + 7;
constexpr int R = 1e7;

int m, n, seed, last = 7;
i64 ac[N], tim[N];

__gnu_pbds::tree<std::pair<int, i64>, null_type, std::greater<std::pair<int, i64>>, rb_tree_tag, tree_order_statistics_node_update> tr;

u32 randNum(u32 last, const u32 m) {
	seed = seed * 17 + last;
	return seed % m + 1;
}

void solve() {
	std::cin >> m >> n >> seed;
	tr.clear();
	for (int i = 1; i <= m; i++) {
		const i64 T = 1.5e12 + 7;
		ac[i] = 0, tim[i] = T + i;
		tr.insert({0, tim[i]});
	}
	for (int i = 1; i <= n; i++) {
		u32 ria = randNum(last, m);
		u32 rib = randNum(last, m);
		tr.erase({ac[ria], tim[ria]});
		++ac[ria], tim[ria] -= 1ll * rib * R;
		tr.insert({ac[ria], tim[ria]});
		last = tr.order_of_key({ac[ria], tim[ria] / R * R + R - 1000});
		std::cout << last << "\n";
	}
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
