#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, tp;
int a[N], st[N], l[N], r[N];
i64 ans, sum[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	for (int i = 1; i <= n; i++) {
		while (tp && a[st[tp]] >= a[i])
			tp--;
		l[i] = st[tp];
		st[++tp] = i;
	}

	tp = 0;
	st[0] = n + 1;
	for (int i = n; i >= 1; i--) {
		while (tp && a[st[tp]] >= a[i])
			tp--;
		r[i] = st[tp] - 1;
		st[++tp] = i;
	}

	for (int i = 1; i <= n; i++)
		ans = std::max(ans, (sum[r[i]] - sum[l[i]]) * a[i]);
	std::cout << ans << "\n";
	return 0;
}
