#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int a[N << 1], b[N << 1];

bool check(int x) {
	for (int i = 1; i <= (n << 1) - 1; i++)
		b[i] = (a[i] >= x);
	for (int i = 0; i < n - 1; i++) {
		if (b[n + i] == b[n + i + 1]) return b[n + i];
		if (b[n - i] == b[n - i - 1]) return b[n - i];
	}
	return b[1];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= (n << 1) - 1; i++)
		std::cin >> a[i];

	int l = 1, r = (n << 1) - 1, x = 0;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (!check(mid)) {
			r = mid;
		} else {
			x = mid;
			l = mid + 1;
		}
	}
	std::cout << x << "\n";
	return 0;
}
