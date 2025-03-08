#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int inf = std::numeric_limits<int>::max();

int n, ans = inf;
int fa[N];

std::pair<int, int> find(int x, int dep) {
	++dep;
	return (fa[x] == x ? std::make_pair(x, dep) : find(fa[x], dep));
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		fa[i] = i;

	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		if (find(x, 0).first == i) {
			ans = std::min(ans, find(x, 0).second);
		} else {
			fa[i] = x;
		}
	}

	std::cout << ans << "\n";
	return 0;
}
