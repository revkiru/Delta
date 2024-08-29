#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int R = 0x3f3f3f3f;

int n, x;
int a[N], sum[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> x;
	for (int i = 1; i < n; i++)
		std::cin >> a[i];

	x <<= 1;
	int j = 0, ret = 0, ans = -R;
	for (int i = 1; i < n; i++) {
		while (j < n && ret < x) { j++; ret += a[j]; }
		ans = std::max(ans, j - i + 1);
		ret -= a[i];
	}
	std::cout << ans << "\n";
	return 0;
}
