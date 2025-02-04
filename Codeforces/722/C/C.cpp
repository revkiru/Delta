#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

i64 n, a[N];
std::multiset<i64> p, sum;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i] += a[i - 1];
	}
	a[n + 1] = a[n];

	sum.insert(a[n]);
	p.insert(0), p.insert(n + 1);
	for (int i = 1; i <= n; i++) {
		i64 x;
		std::cin >> x;
		auto it = p.lower_bound(x);
		i64 r = *it, l = *(--it);
		p.insert(x);
		sum.erase(sum.find(a[r - 1] - a[l]));
		sum.insert(a[x - 1] - a[l]);
		sum.insert(a[r - 1] - a[x]);
		std::cout << *(--sum.end()) << "\n";
	}

	return 0;
}
