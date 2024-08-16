#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, m;
int t0t, cota, cotb;
int ami[N], fa[20][N];
i64 w[N << 1], dis[20][N];

struct edge {
	int to, val;
};
std::vector<edge> G[N << 1];

struct node {
	i64 rest;
	int id;
} a[N], b[N];

void dfs(int x, int lst, i64 dn) {
	fa[0][x] = lst;
	dis[0][x] = dn;
	for (int i = 1; i <= 18; i++) {
		fa[i][x] = fa[i - 1][fa[i - 1][x]];
		dis[i][x] = dis[i - 1][x] + dis[i - 1][fa[i - 1][x]];
	}
	for (size_t i = 0; i < G[x].size(); i++) {
		int y = G[x][i].to, z = G[x][i].val;
		if (y != lst)
			dfs(y, x, z);
	}
}

int vis[N], usd[N], rbj[N];
i64 rmn[N];

bool fndunk(int x, int lst) {	// find unlock: 未被完全封杀 
	int flg = 1, flg0 = 0;
	if (vis[x]) return 1;
	for (size_t i = 0; i < G[x].size(); i++) {
		int y = G[x][i].to, z = G[x][i].val;
		if (y == lst) continue;
		flg0 = 1;
		if (!fndunk(y, x)) {
			flg = 0;
			if (x == 1) {
				b[++cotb].id = y;
				b[cotb].rest = z;
			} else {
				return 0;
			}
		}
	}
	if (!flg0) return 0;
	return flg;
}

bool cmp(const node &p, const node &q) {
	return p.rest > q.rest;
}

bool check(i64 lim) {
	i64 num = 0;
	cota = cotb = 0;
	for (int i = 1; i <= n; i++)
		vis[i] = rbj[i] = 0;
	for (int i = 1; i <= m; i++)
		usd[i] = 0;
	for (int i = 1; i <= m; i++) {
		int x = ami[i];
		num = 0;
		for (int j = 18; j >= 0; j--) {	// 军队起跳 
			if (fa[j][x] > 1 && num + dis[j][x] <= lim) {
				num += dis[j][x];
				x = fa[j][x];
			}
		}
		if (fa[0][x] == 1 && num + dis[0][x] <= lim) {	// 剩余路径 
			a[++cota].rest = lim - num - dis[0][x];
			a[cota].id = i;
			if (!rbj[x] || a[cota].rest < rmn[x]) {
				rmn[x] = a[cota].rest;
				rbj[x] = i;
			}
		} else {
			vis[x] = 1;
		}
	}
	if (fndunk(1, 0)) return 1;
	std::sort(a + 1, a + cota + 1, cmp);	// 子树间转移军队 
	std::sort(b + 1, b + cotb + 1, cmp);
	
	int now = 1;
	usd[0] = 1;
	for (int i = 1; i <= cotb; i++) {
		if (!usd[rbj[b[i].id]]) {
			usd[rbj[b[i].id]] = 1;
			continue;
		}
		while (now <= cota && (usd[a[now].id] || a[now].rest < b[i].rest))
			now++;
		if (now > cota)
			return 0;
		usd[a[now].id] = 1;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i < n; i++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back({v, w});
		G[v].push_back({u, w});
	}
	dfs(1, 0, 0);
	std::cin >> m;
	for (int i = 1; i <= m; i++)
		std::cin >> ami[i];
	i64 l = 0, r = 5e5, ans = -1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		} else {
			l = mid + 1;
		}
	}
	std::cout << ans << "\n";
	return 0;
}
