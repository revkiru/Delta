#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = (1 << 20) + 7;

int n;
int a[N], p[N], ans[N];

std::vector<int> E[N], G[N];

std::stack<int> s;
int tot, t0t, low[N], dfn[N], col[N], vis[N];
void tarjan(int u) {
	low[u] = dfn[u] = ++t0t;
	s.push(u);
	vis[u] = 1;
	for (auto v : E[u]) {
		if (!dfn[v]) {
			tarjan(v);
			low[u] = std::min(low[u], low[v]);
		} else if (vis[v]) {
			low[u] = std::min(low[u], low[v]);
		}
	}
	if (low[u] == dfn[u]) {
		tot++;
		do {
			col[u] = tot;
			u = s.top();
			s.pop();
			vis[u] = 0;
		} while (low[u] != dfn[u]);
	}
}

bool cmp(int i, int j) { return a[i] < a[j]; }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("seq.in", "r", stdin);
	// freopen("seq.out", "w", stdout);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= n; i++)
		E[a[i]].emplace_back(((1 << 20) - 1) ^ a[i]);
	for (int i = 0; i < (1 << 20); i++)
		for (int j = 0; j < 20; j++)
			if ((i >> j) & 1)
				E[i].emplace_back(i ^ (1 << j));
	for (int i = 0; i < (1 << 20); i++)
		if (!dfn[i])
			tarjan(i);
	for (int i = 1; i <= n; i++)
		G[col[a[i]]].push_back(i);
	for (int i = 1; i <= tot; i++) {
		std::sort(G[i].begin(), G[i].end(), cmp);
		for (size_t j = 0; j < G[i].size(); j++)
			p[j] = G[i][j];
		std::sort(G[i].begin(), G[i].end());
		for (size_t j = 0; j < G[i].size(); j++)
			ans[G[i][j]] = a[p[j]];
	}
	for (int i = 1; i <= n; i++)
		std::cout << ans[i] << " ";
	std::cout << "\n";
	return 0;
}
