#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e4 + 7;

int n, ans;
int pri[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		pri[i] = i;
	for (int i = 2; i <= n; i++) {
		if (pri[i] == i) {
			for (int j = i; j <= n; j += i)
				pri[j] = pri[j] * (i - 1) / i;
		}
	}
	for (int i = 1; i < n; i++)
		ans += pri[i];
	if (n == 1) {
		std::cout << "0\n";
	} else {
		std::cout << (ans << 1 | 1) << "\n";
	}
	return 0;
}
