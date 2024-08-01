#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

struct node {
	int w, id;

	bool operator < (const node &x) const {
		return w < x.w;
	}
};

std::priority_queue<node> pq;

int n, c, q;
int l, r;
int a[N], s[N];

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> c >> q;
	while (q--) {
		int op, x;
		std::cin >> op;
		if (op == 1) {
			std::cin >> x;
			a[++n] = x;
			s[n] = s[n - 1] + a[n];
			r = s[n];
			pq.push({x, s[n]});
		} else if (op == 2) {
			std::cin >> x;
			l += x;
		} else if (op == 3) {
			std::cin >> x;
			x += l;
			int p = std::lower_bound(s + 1, s + n + 1, x) - s - 1;
			std::cout << x - s[p] << "\n";
		} else if (op == 4) {
			if (pq.empty()) {
				std::cout << "0\n";
				continue;
			} else {
				while (pq.top().id <= l)
					pq.pop();
				std::cout << pq.top().w << "\n";
			}
		}
	}
	return 0;
}
