#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n;
i64 ans;
std::priority_queue<int, std::vector<int>, std::greater<int>> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		if (!q.empty() && q.top() < x) {
			ans += (x - q.top());
			q.pop();
			q.push(x);
		}
		q.push(x);
	}
	std::cout << ans << "\n";
	return 0;
}
