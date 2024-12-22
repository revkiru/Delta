#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, dp, ans;
int a[N], h[N];

struct Fenwick {
	int tr[N << 2];

	int lowbit(int x) { return x & -x; }

	void add(int i, int x) {
		for (; i <= n; i += lowbit(i))
			tr[i] = std::max(tr[i], x);
	}

	int query(int i) {
		int ret = 0;
		for (; i; i -= lowbit(i))
			ret = std::max(ret, tr[i]);
		return ret;
	}
} bit;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> h[i];
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= n; i++) {
		dp = bit.query(h[i] - 1) + a[i];
		bit.add(h[i], dp);
		ans = std::max(ans, dp);
	}
	std::cout << ans << "\n";
	return 0;
}
