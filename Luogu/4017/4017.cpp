#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int P = 80112002;

int n, m;
int f[N], ind[N], otd[N];

std::vector<int> G[N << 1];

void topo() {
	std::queue<int> q;
	for (int i = 1; i <= n; i++) {
		if (!ind[i]) {
			q.push(i);
			f[i] = 1;
		}
	}
	while (q.size()) {
		int u = q.front();
		q.pop();
		for (auto v : G[u]) {
			ind[v]--;
			f[v] = (f[v] + f[u]) % P;
			if (!ind[v])
				q.push(v);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		G[x].push_back(y);
		G[y].push_back(x);
		ind[y]++, otd[x]++;
	}

	topo();

	i64 ans = 0;
	for (int i = 1; i <= n; i++) {
		if (!otd[i]) {
			ans += f[i] % P;
			ans %= P;
		}
	}
	std::cout << ans << "\n";
	return 0;
}
