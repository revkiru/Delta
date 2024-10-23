#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1007;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m;
int a, b, c;

struct node {
	i64 x, y, dis;

	bool operator < (const node &a) const {
		return dis > a.dis;
	}
};

i64 pth[N][N], dis[3][N][N];
bool vis[N][N];

void dij(int k, int sx, int sy) {
	std::priority_queue<node> q;
	q.push({sx, sy, pth[sx][sy]});
	memset(vis, 0, sizeof(vis));
	
	for (int i = 1; i <= 1000; i++) {
		for (int j = 1; j <= 1000; j++)
			dis[k][i][j] = 1e18;
	}
	dis[k][sx][sy] = pth[sx][sy];
	while (!q.empty()) {
		int x = q.top().x, y = q.top().y;
		q.pop();
		if (vis[x][y])
			continue;
		vis[x][y] = 1;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (nx < 1 || nx > n || ny < 1 || ny > m)
				continue;
			if (dis[k][nx][ny] > dis[k][x][y] + pth[nx][ny]) {
				dis[k][nx][ny] = dis[k][x][y] + pth[nx][ny];
				q.push({nx, ny, dis[k][nx][ny]});
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	std::cin >> a >> b >> c;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++)
			std::cin >> pth[i][j];
	}
	dij(0, 1, a);
	dij(1, n, b);
	dij(2, n, c);

	i64 ans = 1e18;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++)
			ans = std::min(ans, dis[0][i][j] + dis[1][i][j] + dis[2][i][j] - 2 * pth[i][j]);
	}
	std::cout << ans << "\n";
	return 0;
}
