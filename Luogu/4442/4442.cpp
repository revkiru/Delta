#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 507;
constexpr int inf = 0x3f3f3f3f;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int n, m, sx, sy, tx, ty;
int vis[N][N], dis[N][N], b[N][N][4];
char ch[N][N];

struct node {
	int x, y;
};

void bfs() {
	memset(dis, inf, sizeof(dis));
	dis[sx][sy] = 0;
	std::queue<node> q;
	q.push({sx, sy});
	vis[sx][sy] = 1;
	while (!q.empty()) {
		node u = q.front();
		q.pop();
		auto [x, y] = u;
		vis[x][y] = 0;
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];
			if (ch[nx][ny] != '#' && dis[x][y] + 1 < dis[nx][ny]) {
				dis[nx][ny] = dis[x][y] + 1;
				if (!vis[nx][ny]) {
					q.push({nx, ny});
					vis[nx][ny] = 1;
				}
			}
		}
		for (int i = 0; i < 4; i++) {
			auto [x, y] = u;
			int d = b[x][y][i], mn = inf, nx = x + dx[i] * d, ny = y + dy[i] * d;
			for (int j = 0; j < 4; j++) {
				if (i != j)
					mn = std::min(mn, b[x][y][j]);
			}
			mn += dis[x][y] + 1;
			if (dis[nx][ny] > mn) {
				dis[nx][ny] = mn;
				if (!vis[nx][ny]) {
					vis[nx][ny] = 1;
					q.push({nx, ny});
				}
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			std::cin >> ch[i][j];
			if (ch[i][j] == 'C') { sx = i, sy = j; }
			if (ch[i][j] == 'F') { tx = i, ty = j; }
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = m; j; j--) {
			if (ch[i][j] == '#')
				b[i][j][0] = -1;
			else
				b[i][j][0] = b[i][j + 1][0] + 1;
		}
	}
	for (int j = 1; j <= m; j++) {
		for (int i = n; i; i--) {
			if (ch[i][j] == '#')
				b[i][j][1] = -1;
			else
				b[i][j][1] = b[i + 1][j][1] + 1;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (ch[i][j] == '#')
				b[i][j][2] = -1;
			else
				b[i][j][2] = b[i][j - 1][2] + 1;
		}
	}
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) {
			if (ch[i][j] == '#')
				b[i][j][3] = -1;
			else
				b[i][j][3] = b[i - 1][j][3] + 1;
		}
	}
	bfs();
	if (dis[tx][ty] == inf)
		std::cout << "nemoguce\n";
	else
		std::cout << dis[tx][ty] << "\n";
	return 0;
}
