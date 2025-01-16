#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1 << 22;

int n, ans;
int a[N];
std::pair<int, int> f[N];

void insert(int i, int val) {
	if (val > f[i].first) {
		f[i].second = f[i].first;
		f[i].first = val;
	}
	else if (val > f[i].second) {
		f[i].second = val;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];

	for (int i = 1; i <= n; i++)
		insert(a[i], i);
	for (int i = 0; i <= 22; i++) {
		for (int j = 0; j <= 2e6; j++) {
			if ((1 << i) & j) {
				insert((1 << i) ^ j, f[j].first);
				insert((1 << i) ^ j, f[j].second);
			}
		}
	}

	auto check = [&](int msk, int num) -> bool {
		if (f[msk].second >= num)
			return 1;
		return 0;
	};
	for (int i = 1; i < n - 1; i++) {
		int u = 0;
		for (int j = 21; j >= 0; j--) {
			if ((1 << j) & a[i])
				continue;
			if (check(u ^ (1 << j), i))
				u ^= (1 << j);
		}
		ans = std::max(ans, u | a[i]);
	}
	std::cout << ans << "\n";
	return 0;
}
