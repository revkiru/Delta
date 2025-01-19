#include <bits/stdc++.h>

#define int long long

constexpr int N = 5e5 + 7;
constexpr int inf = 2e9;

int n, m;
int a[N], sum[N], f[N];

struct Fenwick {
	int tr[N << 1];

	int lowbit(int x) { return x & -x; }

	void add(int i, int x) {
		for (; i <= n; i += lowbit(i))
			tr[i] = std::min(tr[i], x);
	}

	int query(int i) {
		int ret = inf;
		for (; i; i -= lowbit(i))
			ret = std::min(ret, tr[i]);
		return ret;
	}
} bit;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		a[i] = sum[i] = sum[i - 1] + x;
	}
	std::sort(a + 1, a + n + 2);
	m = std::unique(a + 1, a + n + 2) - a - 1;
	std::fill(bit.tr, bit.tr + (N << 1), inf);
	for (int i = 0; i <= n; i++) {
		int x = std::lower_bound(a + 1, a + m + 1, sum[i]) - a;
		if (!i) { bit.add(x, -1); continue; }
		f[i] = bit.query(x) + i;
		if (sum[i] - sum[i - 1] >= 0)
			f[i] = std::min(f[i], f[i - 1]);
		bit.add(x, f[i] - i - 1);
	}
	if (f[n] > n) std::cout << "-1\n";
	else std::cout << f[n] << "\n";
	return 0;
}
