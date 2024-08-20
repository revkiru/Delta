#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e3 + 7;
constexpr int M = 2e5 + 7;
const int d[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int n, m, k, q;
int id[N][N], dis[N][N];
char s[N][N];

struct UniFind {
	int fa[M], siz[M], wgh[M];
	
	void init() { for (int i = 1; i <= k; i++) fa[i] = i, siz[i] = 1; }
	
	int find(int x) { return fa[x] == x ? x : find(fa[x]); }
	
	void merge(int x, int y, int w) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return;
		if (siz[fx] > siz[fy]) std::swap(fx, fy);
		fa[fx] = fy;
		siz[fy] += siz[fx];
		wgh[fx] = w;
	}
	
	int query(int x, int y) {
		if (find(x) != find(y)) return -1;
		int res = 0;
		while (x != y) {
			if (siz[x] > siz[y]) std::swap(x, y);
			res = std::max(res, wgh[x]);
			x = fa[x];
		}
		return res;
	}
} uni;

int t0t;
struct edge {
	int u, v, w;
	bool operator < (const edge &adj) const {
		return w < adj.w;
	}
} e[N * N << 1];

std::queue<int> que;
void bfs() {
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		int x = (u - 1) / m + 1, y = (u - 1) % m + 1;
		for (int i = 0; i < 4; i++) {
			int nx = x + d[i][0], ny = y + d[i][1];
			if (nx < 1 || nx > n || ny < 1 || ny > m || s[nx][ny] == '#' || id[x][y] == id[nx][ny])
				continue;
			if (id[nx][ny])
				e[++t0t] = {id[x][y], id[nx][ny], dis[x][y] + dis[nx][ny]};
			else {
				que.push((nx - 1) * m + ny);
				id[nx][ny] = id[x][y];
				dis[nx][ny] = dis[x][y] + 1;
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m >> k >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> (s[i] + 1);
	memset(dis, 0x3f, sizeof(dis));
	for (int i = 1; i <= k; i++) {
		int x, y;
		std::cin >> x >> y;
		id[x][y] = i, dis[x][y] = 0;
		que.push((x - 1) * m + y);
	}
	uni.init();
	bfs();
	std::sort(e + 1, e + t0t + 1);
	for (int i = 1; i <= t0t; i++)
		uni.merge(e[i].u, e[i].v, e[i].w);
	for (int i = 1; i <= q; i++) {
		int x, y;
		std::cin >> x >> y;
		std::cout << uni.query(x, y) << "\n";
	}
	return 0;
}
