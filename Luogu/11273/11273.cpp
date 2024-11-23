#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n, k;
	std::cin >> n >> k;
	std::vector<std::pair<int, int>> a(n + 1);

	#define x first
	#define y second

	for (int i = 1; i <= n; i++) {
		std::cin >> a[i].x;
		a[i].y = i;
	}
	std::sort(a.begin() + 1, a.end(), std::greater<std::pair<int, int>>());
	std::vector<int> f(n + 1);
	f[a[1].y] = 0;
	for (int i = 2; i <= n; i++) {
		f[a[i].y] = std::max(0, f[a[i - 1].y] + 1 - (a[i - 1].x == a[i].x) - (a[i - 1].x - a[i].x - 1) / k);
	}
	for (int i = 1; i <= n; i++) {
		std::cout << f[i] << " ";
	}
	std::cout << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	solve();
	return 0;
}
