#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace __gnu_pbds;
using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;
int fa[N];
bool del[N];

__gnu_pbds::priority_queue<std::pair<int, int>, std::greater<std::pair<int, int>>, pairing_heap_tag> q[N];

int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

int main() {
	std::cin >> n >> m;
	for (int i = 1, x; i <= n; i++) {
		fa[i] = i;
		std::cin >> x;
		q[i].push({x, i});
	}
	while (m--) {
		int opt, x, y;
		std::cin >> opt;
		if (opt == 1) {
			std::cin >> x >> y;
			int fx = find(x), fy = find(y);
			if (fx == fy || del[x] || del[y]) {
				continue;
			}
			if (q[fx].size() >= q[fy].size()) {
				fa[fy] = fx;
				q[fx].join(q[fy]);
			} else {
				fa[fx] = fy;
				q[fy].join(q[fx]);
			}
		} else {
			std::cin >> x;
			if (del[x]) {
				std::cout << "-1\n";
				continue;
			}
			int fx = find(x);
			auto u = q[fx].top();
			std::cout << u.first << "\n";
			del[u.second] = 1;
			q[fx].pop();
		}
	}
	return 0;
}
