#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n;
bool vis[N];
std::vector<int> pri;

void init(const int n) {
	memset(vis, 0, sizeof(vis));
	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;
		pri.push_back(i);
		for (int j = i; j <= n / i; j++)
			vis[i * j] = 1;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	init(n);
	for (int i = 0; i < pri.size(); i++) {
		int p = pri[i], c = 0;
		for (int j = n; j; j /= p)
			c += (j / p);
		std::cout << p << " " << c << "\n";
	}
	return 0;
}
