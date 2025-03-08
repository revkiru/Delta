#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, m;
int ind[N], f[N];

std::vector<std::pair<int, int>> G[N << 1];

void topo() {
	std::queue<int> q;
	memset(f, -0x3f, sizeof(f));
	f[1] = 0, f[n] = -1;
	q.push(1);
	for (int i = 2; i <= n; i++) {
		if (!ind[i])
			q.push(i);
	}

	while (q.size()) {
		int u = q.front();
		q.pop();
		for (auto [v, w] : G[u]) {
			f[v] = std::max(f[v], f[u] + w);
			ind[v]--;
			if (!ind[v]) { q.push(v); }
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, x, y, z; i <= m; i++) {
		std::cin >> x >> y >> z;
		G[x].push_back({y, z});
		ind[y]++;
	}
	topo();
	std::cout << f[n] << "\n";
	return 0;
}
