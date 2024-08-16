#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int l, n, m;
int a[N], d[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> l >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		d[i] = a[i] - a[i - 1];
	}
	d[n + 1] = l - a[n];
	
	int _l = 1, _r = l;
	while (_l < _r) {
		int sum = 0;
		for (int i = 1; i <= n + 1; i++)
			a[i] = d[i];
		int mid = (_l + _r + 1) >> 1;
		for (int i = 1; i <= n + 1; i++) {
			if (a[i] < mid) {
				sum++;
				a[i + 1] += a[i];
			}
		}
		if (sum <= m) _l = mid;
		else _r = mid - 1;
	}
	
	std::cout << _l << "\n";
	return 0;
}
