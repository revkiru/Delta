#include <bits/stdc++.h>

using i64 = long long;

int a[] = {0, 4, 10, 20, 35, 56, 83, 116, 155, 198, 244, 292, 341};

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	i64 n;
	std::cin >> n;
	if (n <= 12)
		std::cout << a[n];
	else
		std::cout << (i64) (341 + (i64) (n - 12) * 49) << "\n";
	return 0;
}
