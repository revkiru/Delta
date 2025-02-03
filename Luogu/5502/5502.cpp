#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
i64 ans, a[N];
std::queue<int> q1, q2;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	a[0] = -1;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		int lst = 0;
		while (q1.size()) {
			int x = q1.front();
			q1.pop();
			a[x] = std::__gcd(a[x], a[i]);
			ans = std::max(ans, a[x] * (i - x + 1));
			if (a[x] == a[lst])
				continue;
			q2.push(x);
			lst = x;
		}
		ans = std::max(ans, a[i]);
		while (q2.size()) {
			q1.push(q2.front());
			q2.pop();
		}
		if (a[lst] != a[i])
			q1.push(i);
	}
	std::cout << ans << "\n";
	return 0;
}
