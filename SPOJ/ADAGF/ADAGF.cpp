#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;

int n;
int a[N];
std::map<int, int> mp1, mp2;

int cdq(int l, int r) {
	if (l == r)
		return a[l];
	int mid = (l + r) >> 1;
	mp1.clear(), mp2.clear();

	int gcd1 = a[mid], gcd2 = a[mid + 1];
	for (int i = mid; i >= l; i--) {
		gcd1 = std::__gcd(gcd1, a[i]);
		mp1[gcd1]++;
	}
	for (int i = mid + 1; i <= r; i++) {
		gcd2 = std::__gcd(gcd2, a[i]);
		mp2[gcd2]++;
	}

	int res = 0;
	for (auto [u, v] : mp1) {
		for (auto [_u, _v] : mp2)
			res += v * _v * std::__gcd(u, _u);
	}

	return res + cdq(l, mid) + cdq(mid + 1, r);
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	std::cout << cdq(1, n) << "\n";
	return 0;
}
