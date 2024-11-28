#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int a[N], w[N];

void solve() {
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	a[n + 1] = 0;

	i64 ans = 0;
	std::stack<int> s;
	for (int i = 1; i <= n + 1; i++) {
		if (!s.empty() && a[i] > s.top()) {
			s.push(a[i]);
			w[s.size()] = 1;
		} else {
			int wid = 0;
			while (!s.empty() && s.top() > a[i]) {
				wid += w[s.size()];
				ans = std::max(ans, (i64) wid * s.top());
				s.pop();
			}
			s.push(a[i]);
			w[s.size()] = wid + 1;
		}
	}
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	while (std::cin >> n && n)
		solve();
	return 0;
}
