#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int R = 1e6;

int n, m;
int a[N << 1], ans[N << 1];
bool vis[N];

struct Fenwick {
	int tr[N << 2];

	int lowbit(int x) { return x & -x; }

	void add(int x, int v) {
		for (; x <= (R << 1); x += lowbit(x))
			tr[x] += v;
	}

	int query(int x) {
		int res = 0;
		for (; x; x -= lowbit(x))
			res += tr[x];
		return res;
	}
} bit;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	for (int i = 1; i <= R; i++)
		bit.add(i + R, 1);

	std::cin >> n >> m;
	for (int i = 1, x, y, p = R; i <= m; i++) {
		std::cin >> x >> y;
		int l = 1, r = R << 1, pos = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (bit.query(mid) < y)
				pos = l = mid + 1;
			else
				r = mid - 1;
		}
		if (pos > R) {
			if (vis[x]) { std::cout << "-1\n"; exit(0); }
			vis[x] = 1;
			ans[pos - R] = x;
		} else {
			if (a[pos] != x) { std::cout << "-1\n"; exit(0); }
		}
		a[p] = x;
		bit.add(pos, -1);
		bit.add(p--, 1);
	}
	for (int i = 1, j = 1; i <= n; i++) {
		if (!ans[i]) {
			while (vis[j]) j++;
			ans[i] = j;
			vis[j] = 1;
		}
		std::cout << ans[i] << " ";
	}
	std::cout << "\n";
	return 0;
}
