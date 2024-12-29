#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;
constexpr int inf = 2e9;

int n, q, k;
int a[N], b[N], sum[N], prm[N], prb[N];

bool check(int x) {
	int cot = std::lower_bound(a + 1, a + n + 1, x) - a - 1;
	if (!cot) {
		if (n != 1 || k & 1)
			return 1;
		return a[1] - k / 2 >= x;
	}
	if (prm[cot] + k < x)
		return 0;
	if (k <= n)
		return 1;
	if (k - cot & 1)
		return n > cot;
	if (n - cot >= 2)
		return 1;
	return prb[cot] + k * cot + sum[n] - sum[cot] - n * x >= (k - cot) / 2;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i];
	prm[0] = inf;
	for (int i = 1; i <= n; i++) {
		b[i] = a[i] - i + 1;
		prb[i] = prb[i - 1] + b[i];
		prm[i] = std::min(prm[i - 1], b[i]);
	}
	while (q--) {
		std::cin >> k;
		int l = -1e18, r = 1e18, ans = 0;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ans = mid;
				l = mid + 1;
			} else
				r = mid;
		}
		std::cout << ans << " ";
	}
	std::cout << "\n";
	return 0;
}
