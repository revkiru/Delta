#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, k, _l, _r;
i64 sum[N];

struct RMQ {
	i64 rmax[N][20];
	
	void init(const int n) {
		for (int i = 1; i <= n; i++)
			rmax[i][0] = i;
		for (int j = 1; (1 << j) <= n; j++) {
			for (int i = 1; i + (1 << j) - 1 <= n; i++) {
				int x = rmax[i][j - 1];
				int y = rmax[i + (1 << (j - 1))][j - 1];
				rmax[i][j] = sum[x] > sum[y] ? x : y;
			}
		}
	}
	
	int query_max(int l, int r) {
		int k = std::__lg(r - l + 1);
		int x = rmax[l][k], y = rmax[r - (1 << k) + 1][k];
		return sum[x] > sum[y] ? x : y;
	}
} tab;

struct node {
	int o, l, r, t;

	node() {}

	node(int o, int l, int r) : o(o), l(l), r(r), t(tab.query_max(l, r)) {}

	bool operator < (const node &rhs) const {
		return sum[t] - sum[o - 1] < sum[rhs.t] - sum[rhs.o - 1];
	}
};

std::priority_queue<node> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k >> _l >> _r;
	for (int i = 1; i <= n; i++) {
		std::cin >> sum[i];
		sum[i] += sum[i - 1];
	}

	tab.init(n);
	for (int i = 1; i <= n; i++) {
		if (i + _l - 1 <= n)
			q.push(node(i, i + _l - 1, std::min(n, i + _r - 1)));
	}

	i64 ans = 0;
	while (k--) {
		auto [o, l, r, t] = q.top();
		q.pop();
		ans += sum[t] - sum[o - 1];
		if (l != t)
			q.push({o, l, t - 1});
		if (r != t)
			q.push({o, t + 1, r});
	}
	std::cout << ans << "\n";
	return 0;
}
