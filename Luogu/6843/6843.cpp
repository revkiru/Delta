#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3007;

int n, m, k, s, t, dfn;
int a[N], len[N], q[N];
int st[N], seq[N], ed[N], f[1 << 22];
bool ans[N];
std::vector<int> G[N << 1], Gp[N << 1];

void dfs1(int x) {
	q[++t] = a[x];
	seq[st[x] = ++dfn] = a[x];
	for (auto y : G[x]) {
		for (int j = 1; j <= t; j++) {
			int _k = k - s - a[x] - len[y] + q[j];
			if (_k >= 0 && _k <= k)
				if (f[_k]) { ans[y] = 1; break; }
		}
	}
	for (auto y : Gp[x])
		dfs1(y);
	t--;
	ed[x] = dfn;
}

void dfs2(int x) {
	for (int i = st[x]; i <= ed[x]; i++)
		f[seq[i] - a[x] + s]++;
	for (auto y : G[x]) {
		if (ans[y]) continue;
		int _k = k - a[x] - len[y];
		for (int j = 1; j * j <= _k; j++) {
			if (_k % j == 0)
				if (f[j] || f[_k / j]) { ans[y] = 1; break; }
		}
	}
	for (auto y : Gp[x])
		dfs2(y);
	for (int i = st[x]; i <= ed[x]; i++)
		f[seq[i] - a[x] + s]--;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> k >> s;
	s++;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x >> a[i];
		a[i] += a[x] + 1;
		Gp[x].push_back(i);
	}
	for (int i = 1, x; i <= m; i++) {
		std::cin >> x >> len[i];
		len[i]++;
		ans[i] = a[x] + len[i] == k;
		if (!ans[i])
			G[x].push_back(i);
	}
	for (int i = 0; i <= n; i++)
		f[a[i]] = 1;
	dfs1(0);
	for (int i = 0; i <= n; i++)
		f[a[i]] = 0;
	dfs2(0);
	for (int i = 1; i <= m; i++)
		std::cout << (ans[i] ? "YES" : "NO") << "\n";
	return 0;
}
