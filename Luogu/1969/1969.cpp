#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, ans;
int h[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> h[i];
	for (int i = 1; i <= n; i++) {
		if (h[i] > h[i - 1])
			ans += h[i] - h[i - 1];
	}
	std::cout << ans << "\n";
	return 0;
}
