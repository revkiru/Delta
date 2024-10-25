#include <bits/stdc++.h>

using i64 = long long;

int n;
std::map<std::string, bool> mp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::string s;
		std::cin >> s;
		mp[s] = 1;
	}
	std::cout << mp.size() << "\n";
	return 0;
}
