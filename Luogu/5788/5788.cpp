#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e6 + 7;

int n;
i64 a[N], f[N];

std::stack<i64> s;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}

	for (int i = n; i >= 1; i--) {
		while (!s.empty() && a[s.top()] <= a[i])
			s.pop();
		f[i] = (s.empty() ? 0ll : s.top());
		s.push(i);
	}

	for (int i = 1; i <= n; i++) {
		std::cout << f[i] << " ";
	}
	std::cout << "\n";
	return 0;
}
