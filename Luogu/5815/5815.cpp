#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 57;
constexpr i64 R = 2.5e10;

int n, m;
int c[N];

bool check(i64 u) {
	i64 lim1 = 0, lim2 = u;
	for (int i = 1; i <= n; i++) {
		if (c[i] >= u)
			continue;
		lim1 += (u - c[i]);
		lim2 -= (u - c[i]);
		if (lim1 > m || lim2 < 0)
			return 0;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> c[i];
	i64 l = 1, r = R;
	while (l < r) {
		i64 mid = (l + r + 1) >> 1;
		if (check(mid))
			l = mid;
		else
			r = mid - 1;
	}
	std::cout << l << "\n";
	return 0;
}
