#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, k, cnt;
i64 m;
int p[N], p2[N], cyc[N], ans[N];
std::vector<int> s[N], r[N], ns[N], c[N];

int t[N];
void add(std::vector<int> &vec, int &res) {
	for (auto i : vec) {
		if (!t[i])
			res++;
		t[i]++;
	}
}

void del(std::vector<int> &vec, int &res) {
	for (auto i : vec) {
		t[i]--;
		if (!t[i])
			res--;
	}
}

void dfs(int u, int now) {
	if (cyc[u]) return;
	cyc[u] = now;
	for (auto v : s[u])
		ns[now].push_back(v);
	c[now].push_back(u);
	dfs(p2[u], now);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k >> m;
	for (int i = 1; i <= n; i++) {
		s[i].push_back(i);
		p[i] = i;
	}
	for (int i = 1, a, b; i <= k; i++) {
		std::cin >> a >> b;
		s[p[a]].push_back(b);
		s[p[b]].push_back(a);
		std::swap(p[a], p[b]);
		if (i == m % k) {
			for (int j = 1; j <= n; j++)
				r[j] = s[j];
		}
	}
	for (int i = 1; i <= n; i++)
		p2[p[i]] = i;
	for (int i = 1; i <= n; i++) {
		if (!cyc[i]) {
			cnt++;
			dfs(i, cnt);
		}
	}

	i64 o = m / k;
	for (int i = 1; i <= cnt; i++) {
		int res = 0;
		memset(t, 0, sizeof(t));
		if (o >= c[i].size()) {
			add(ns[i], res);
			for (int j = 0; j < c[i].size(); j++) {
				int num = c[i][j];
				add(r[num], res);
				ans[num] = res;
				del(r[num], res);
			}
		} else if (o == 0) {
			for (int j = 0; j < c[i].size(); j++) {
				int num = c[i][j];
				add(r[num], res);
				ans[num] = res;
				del(r[num], res);
			}
		} else {
			for (int j = 0; j < o - 1; j++) {
				int num = c[i][j];
				add(s[num], res);
			}
			for (int j = 0; j < c[i].size(); j++) {
				int nxt = c[i][(j + o) % c[i].size()],
					now = c[i][(j + o - 1) % c[i].size()],
					num = c[i][j];
				add(s[now], res);
				add(r[nxt], res);
				ans[num] = res;
				del(r[nxt], res);
				del(s[num], res);
			}
		}
	}

	for (int i = 1; i <= n; i++)
		std::cout << ans[i] << "\n";
	return 0;
}
