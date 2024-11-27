#include <bits/stdc++.h>

using i64 = long long;

#define num(i, j) ((i - 1) * m + j)

constexpr int N = 107;
constexpr int M = 27;

int n, m, t, act, p;
int a[M][M], c[M][M];
i64 f[N], d[N][N], e[N][N][N];
std::string s, b[M];

// int num(int i, int j) { return (i - 1) * m + j; }

void mulSelf(i64 a[N][N], i64 b[N][N]) {
	i64 w[N][N] = { 0 };
	for (int i = 1; i <= p; i++) {
		for (int k = 1; k <= p; k++)
			if (a[i][k])
				for (int j = 1; j <= p; j++)
					w[i][j] += a[i][k] * b[k][j];
	}
	memcpy(a, w, sizeof(w));
}

void mulRhs(i64 a[N], i64 b[N][N]) {
	i64 w[N] = { 0 };
	for (int i = 1; i <= p; i++) {
		for (int j = 1; j <= p; j++)
			w[i] += a[j] * b[j][i];
	}
	memcpy(f, w, sizeof(w));
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> t >> act;
	for (int i = 1; i <= n; i++) {
		std::cin >> s;
		s = '$' + s;
		for (int j = 1; j <= m; j++)
			a[i][j] = s[j] - '0' + 1;
	}
	for (int i = 1; i <= act; i++)
		std::cin >> b[i];
	p = n * m + 1;
	for (int k = 1; k <= 60; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				int x = a[i][j], y = c[i][j];
				if (b[x][y] >= '0' && b[x][y] <= '9') {
					e[k][p][num(i, j)] = b[x][y] - '0';
					e[k][num(i, j)][num(i, j)] = 1;
				}
				if (b[x][y] == 'N' && i > 1)
					e[k][num(i, j)][num(i - 1, j)] = 1;
				if (b[x][y] == 'W' && j > 1)
					e[k][num(i, j)][num(i, j - 1)] = 1;
				if (b[x][y] == 'S' && i < n)
					e[k][num(i, j)][num(i + 1, j)] = 1;
				if (b[x][y] == 'E' && j < m)
					e[k][num(i, j)][num(i, j + 1)] = 1;
				c[i][j] = (y + 1) % b[x].size();
			}
		}
		e[k][p][p] = 1;
	}
	memcpy(d, e[1], sizeof(e[1]));
	for (int k = 2; k <= 60; k++)
		mulSelf(d, e[k]);
	i64 ans = 0, w = t / 60;
	f[p] = 1;
	for (; w; w >>= 1) {
		if (w & 1)
			mulRhs(f, d);
		mulSelf(d, d);
	}
	w = t % 60;
	for (int i = 1; i <= w; i++)
		mulRhs(f, e[i]);
	for (int i = 1; i <= p; i++)
		ans = std::max(ans, f[i]);
	std::cout << ans << "\n";
	return 0;
}
