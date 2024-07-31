#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int R = 1e5;

i64 x, k, cot, tot;
i64 p[N];

void init() {
	for (i64 i = 1; i * i <= x; i++) {
		if (x % i == 0)
			p[++cot] = i;
	}
	for (i64 i = cot; i >= 1; i--) {
		if (p[i] * p[i] != x)
			p[++cot] = x / p[i];
	}
}

void dfs(i64 sum, i64 k) {
	if (tot >= R) return;
	if (k == 0 || sum == 1) {
		std::cout << sum << " ";
		tot++;
		return;
	}
	for (int i = 1; i <= cot; i++) {
		if (sum % p[i] == 0)
			dfs(p[i], k - 1);
		if (sum < p[i] || tot > R) return;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> x >> k;
	init();
	dfs(x, k);
	std::cout << "\n";
	return 0;
}
