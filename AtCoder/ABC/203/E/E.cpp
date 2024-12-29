#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, m;
std::set<int> st;
std::map<int, std::vector<int>> a;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		a[x].push_back(y);
	}

	st.insert(n);
	for (auto i : a) {
		std::vector<int> del, add;
		for (auto j : i.second)
			if (st.count(j))
				del.push_back(j);
		for (auto j : i.second)
			if (st.count(j - 1) || st.count(j + 1))
				add.push_back(j);
		for (auto j : del)
			st.erase(j);
		for (auto j : add)
			st.insert(j);
	}

	std::cout << st.size() << "\n";
	return 0;
}
