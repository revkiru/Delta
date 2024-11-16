#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 15;
constexpr i64 inf = 1e18;
const int p[N] = {0, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

i64 n, cnt = 1, ans = inf;
i64 c[N];

void dfs(i64 u, i64 num, i64 cnt0) {
	if (u == 11) {
		if (cnt0 > cnt || (cnt0 == cnt && ans > num)) {
			cnt = cnt0;
			ans = num;
		}
		return;
	}
	i64 num0 = num;
	for (int i = 0; i <= c[u - 1]; i++) {
		if (num0 > n)
			return;
		c[u] = i;
		dfs(u + 1, num0, cnt0 * (i + 1));
		num0 *= p[u];
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	c[0] = inf;
	dfs(1, 1, 1);
	std::cout << ans << "\n";
	return 0;
}
