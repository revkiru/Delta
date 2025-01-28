#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e4 + 7;
constexpr int inf = 1e9;

int n;
int c[N];
std::pair<int, int> a[N];

void clear(int t) {
	for (int i = 1; i <= n; i++)
		if (c[i] == t)
			c[i] = 0;
}

void cover(int x, int y, int l, int t) {
	for (int i = 1; i <= n; i++) {
		if (c[i] || x - l > a[i].first || x < a[i].first || y < a[i].second || y - l > a[i].second)
			continue;
		c[i] = t;
	}
}

int dfs(int l, int t) {
	int cnt = 0, xmx = -inf, ymx = -inf, xmn = inf, ymn = inf;
	for (int i = 1; i <= n; i++) {
		if (c[i]) continue;
		xmx = std::max(xmx, a[i].first);
		xmn = std::min(xmn, a[i].first);
		ymx = std::max(ymx, a[i].second);
		ymn = std::min(ymn, a[i].second);
		cnt++;
	}
	if (t > 3) return !cnt;

	cover(xmx, ymn + l, l, t);
	if (dfs(l, t + 1)) return 1;
	clear(t);
	cover(xmx, ymx, l, t);
	if (dfs(l, t + 1)) return 1;
	clear(t);
	cover(xmn + l, ymn + l, l, t);
	if (dfs(l, t + 1)) return 1;
	clear(t);
	cover(xmn + l, ymx, l, t);
	if (dfs(l, t + 1)) return 1;
	clear(t);

	return 0;
}

bool check(int x) {
	for (int i = 1; i <= n; i++)
		c[i] = 0;
	return dfs(x, 1);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i].first >> a[i].second;
	int l = 0, r = 2e9;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	std::cout << l << "\n";
	return 0;
}
