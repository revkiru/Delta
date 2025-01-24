#include <bits/stdc++.h>

using i64 = long long;

int n;
std::vector<std::pair<int, int>> a, b;

bool cmp1(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	if (a.first != b.first) return a.first < b.first;
	return a.second > b.second;
}

bool cmp2(const std::pair<int, int> &a, const std::pair<int, int> &b) {
	if (a.second != b.second) return a.second > b.second;
	return a.first < b.first;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x, y; i <= n; i++) {
		std::cin >> x >> y;
		if (x <= y)
			a.push_back({x, y});
		else
			b.push_back({x, y});
	}

	std::sort(a.begin(), a.end(), cmp1);
	std::sort(b.begin(), b.end(), cmp2);

	i64 ans = 0, cnt = 0;
	for (auto i : a) {
		if (cnt >= i.first) {
			cnt -= i.first;
			cnt += i.second;
		} else {
			ans += (i.first - cnt);
			cnt = i.second;
		}
	}
	for (auto i : b) {
		if (cnt >= i.first) {
			cnt -= i.first;
			cnt += i.second;
		} else {
			ans += (i.first - cnt);
			cnt = i.second;
		}
	}
	std::cout << ans << "\n";
	return 0;
}
