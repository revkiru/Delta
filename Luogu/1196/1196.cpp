#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n;
int fa[N], s[N], b[N];

void init(const int n) {
	for (int i = 1; i <= n; i++) {
		fa[i] = i;
		s[i] = 0;
		b[i] = 1;
	}
}

int find(int x) {
	if (fa[x] == x) return x;
	int k = fa[x];
	fa[x] = find(fa[x]);
	s[x] += s[k];
	b[x] = b[fa[x]];
	return fa[x];
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	init(n);
	for (int i = 1; i <= n; i++) {
		char ch; int x, y;
		std::cin >> ch >> x >> y;
		if (ch == 'M') {
			int fx = find(x), fy = find(y);
			fa[fx] = fy;
			s[fx] += b[fy];
			b[fx] += b[fy];
			b[fy] = b[fx];
		}
		if (ch == 'C') {
			int fx = find(x), fy = find(y);
			if (fx != fy) {
				std::cout << "-1\n";
				continue;
			}
			std::cout << std::abs(s[x] - s[y]) - 1 << "\n";
		}
	}
	return 0;
}
