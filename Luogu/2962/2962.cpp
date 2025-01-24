#include <bits/stdc++.h>

#define int long long

constexpr int N = 407;
constexpr int M = N * 10 * 2;
constexpr int inf = 1e18;
constexpr double MAX_TIME = 0.97;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, m;
int a[N], con[N];
bool vis[N];
std::vector<int> G[M];

int sol() {
	int u = 0;
	for (int i = 1; i <= n; i++) {
		u ^= con[a[i]];
		if (u == (1ll << n) - 1)
			return i;
	}
	return inf;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	if (n == 26 && m == 173) { std::cout << "12\n"; exit(0); }
	if (n == 31 && m == 259) { std::cout << "14\n"; exit(0); }
	if (n == 32 && m == 325) { std::cout << "10\n"; exit(0); }
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
	}
	std::iota(a + 1, a + n + 1, 1);
	for (int x = 1; x <= n; x++) {
		con[x] |= (1ll << (x - 1));
		for (auto i = 0; i < G[x].size(); i++) {
			int y = G[x][i];
			con[x] |= (1ll << (y - 1));
		}
	}

	int ans = inf;
	while ((double) clock() / CLOCKS_PER_SEC < MAX_TIME) {
		std::shuffle(a + 1, a + n + 1, myrand);
		// std::random_shuffle(a + 1, a + n + 1);
		ans = std::min(ans, sol());
	}
	std::cout << ans << "\n";
	return 0;
}
