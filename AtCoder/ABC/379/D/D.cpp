#include <bits/stdc++.h>

#define int long long

void solve() {
	int q, h = 0;
	std::cin >> q;
	std::priority_queue<int> pq;
	while (q--) {
		int opt;
		std::cin >> opt;
		if (opt == 1) {
			pq.push(-h);
		}
		if (opt == 2) {
			int x;
			std::cin >> x;
			h += x;
		}
		if (opt == 3) {
			int x, ret = 0;
			std::cin >> x;
			while (!pq.empty()) {
				int t = pq.top();
				if (t + h >= x) {
					ret++;
					pq.pop();
				} else {
					break;
				}
			}
			std::cout << ret << "\n";
		}
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
