#include <bits/stdc++.h>

using i64 = long long;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar_unlocked();
	for (; !isdigit(ch); ch = getchar_unlocked()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar_unlocked()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar_unlocked('-'); }
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + '0');
}

void solve() {
	int n = read<int>(), m = read<int>(), q = read<int>();
	std::vector<int> G[m + 1];
	std::vector<bool> vis(m + 1);
	for (int x = 1; x <= m; x++) {
		for (int i = 1, p; i <= n; i++) {
			p = read<int>();
			G[x].push_back(p);
		}
	}
	while (q--) {
		int opt = read<int>(), x = read<int>(), y = read<int>();
		if (opt == 2) {
			write<int>(G[x][y - 1]);
			puts("");
		} else {
			if (vis[x] && vis[y]) {
				/*if (*G[x].end() <= *G[y].begin())
					continue;
				if (*G[y].end() <= *G[x].begin()) {
					std::swap(G[x], G[y]);
					continue;
				}*/
				if (G[x][G[x].size() - 1] <= G[y][0])
					continue;
				if (G[y][G[y].size() - 1] <= G[x][0]) {
					std::swap(G[x], G[y]);
					continue;
				}
			}
			std::vector<int> v;
			v.insert(v.end(), G[x].begin(), G[x].end());
			v.insert(v.end(), G[y].begin(), G[y].end());
			std::sort(v.begin(), v.end());
			for (int i = 0; i < n; i++)
				G[x][i] = v[i];
			for (int i = n; i < v.size(); i++)
				G[y][i - n] = v[i];
			vis[x] = vis[y] = 1;
		}
	}
}

int main() {
	// std::ios::sync_with_stdio(false);
	// std::cin.tie(nullptr);

	solve();
	return 0;
}
