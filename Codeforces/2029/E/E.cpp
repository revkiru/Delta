#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e5 + 7;

int g[N];

void init() {
	const int R = 4e5;
	for (int i = 2; i * i <= R; i++) {
		if (!g[i]) {
			for (int j = i * i; j <= R; j += i)
				if (!g[j])
					g[j] = i;
		}
	}
}

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n + 1);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
	}
	
	int pri = 0;
	for (int i = 1; i <= n; i++) {
		if (!g[a[i]]) {
			if (!pri) {
				pri = a[i];
			} else if (pri != a[i]) {
				std::cout << "-1\n";
				return;
			}
		}
	}

	if (!pri) {
		std::cout << "2\n";
		return;
	}

	for (int i = 1; i <= n; i++) {
		if (a[i] == pri)
			continue;
		if (a[i] - (a[i] & 1 ? g[a[i]] : 0) < (pri * 2)) {
			std::cout << "-1\n";
			return;
		}
	}
	std::cout << pri << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	init();
	while (t--) {
		solve();
	}
	return 0;
}
