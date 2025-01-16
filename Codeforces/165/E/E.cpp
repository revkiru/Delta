#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n;
int a[N], f[1 << 22];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		f[a[i]] = a[i];
	}

	for (int i = 0; i < 22; i++) {
		for (int j = 0; j < (1 << 22); j++)
			if (j & (1 << i) && f[j ^ (1 << i)])
				f[j] = f[j ^ (1 << i)];
	}

	for (int i = 1; i <= n; i++) {
		int b = ((1 << 22) - 1) ^ a[i];
		std::cout << (f[b] ? f[b] : -1) << " ";
	}
	std::cout << "\n";
	return 0;
}
