#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::cin >> n;
	std::priority_queue<int, std::vector<int>, std::greater<int>> q;
	for (int i = 1; i <= n; i++) {
		std::vector<int> a(n + 1);
		for (int j = 1; j <= n; j++)
			std::cin >> a[j];
		int j = n;
		for (; j >= 1 && a[j] == 1; j--);
		q.push(n - j);
	}

	int mex = 0;
	for (; q.size(); mex++) {
		while (q.size() && q.top() < mex)
			q.pop();
		if (q.empty())
			break;
		q.pop();
	}
	std::cout << mex << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
