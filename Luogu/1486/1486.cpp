#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int long long

using namespace __gnu_pbds;

int n, m, dlt, ans;
__gnu_pbds::tree<std::pair<int, int>, null_type, std::greater<std::pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> tr, tr0;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, k; i <= n; i++) {
		char opt;
		std::cin >> opt >> k;
		if (opt == 'I') {
			k += dlt;
			if (k >= m)
				tr.insert({k, i});
		}
		if (opt == 'A') {
			m -= k;
			dlt -= k;
		}
		if (opt == 'S') {
			m += k;
			dlt += k;
			tr.split({m, - 1}, tr0);
			ans += tr0.size();
			tr0.clear();
		}
		if (opt == 'F') {
			if (tr.size() >= k) {
				std::cout << tr.find_by_order(k - 1)->first - dlt << "\n";
			} else {
				std::cout << "-1\n";
			}
		}
	}
	std::cout << ans << "\n";
	return 0;
}
