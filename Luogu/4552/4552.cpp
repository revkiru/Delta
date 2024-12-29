#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;

int n, cur1, cur2;
int a[N], b[N];

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	b[1] = a[1];
	for (int i = 2; i <= n; i++) {
		b[i] = a[i] - a[i - 1];
		if (b[i] > 0)
			cur1 += b[i];
		else
			cur2 -= b[i];
	}
	std::cout << std::max(cur1, cur2) << "\n" << std::abs(cur1 - cur2) + 1 << "\n";
	return 0;
}
