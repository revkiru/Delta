#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 20;

int ia, ib, ic, id;
double f[N][N][N][N][5][5];
bool v[N][N][N][N][5][5];

void init() {
	memset(f, 0, sizeof(f));
	memset(v, 0, sizeof(v));
}

void myAdd(int x, int &a, int &b, int &c, int &d) {
	if (x == 1)
		a++;
	if (x == 2)
		b++;
	if (x == 3)
		c++;
	if (x == 4)
		d++;
}

double dp(int a, int b, int c, int d, int x, int y) {
	if (v[a][b][c][d][x][y])
		return f[a][b][c][d][x][y];
	v[a][b][c][d][x][y] = 1;
	double &ans = f[a][b][c][d][x][y] = 0;
	int na = a, nb = b, nc = c, nd = d;
	myAdd(x, na, nb, nc, nd);
	myAdd(y, na, nb, nc, nd);
	if (na >= ia && nb >= ib && nc >= ic && nd >= id)
		return 0;
	int w = 54 - na - nb - nc - nd;
	if (w <= 0)
		return ans = 1e9;
	if (a < 13)
		ans += dp(a + 1, b, c, d, x, y) * (13 - a) / w;
	if (b < 13)
		ans += dp(a, b + 1, c, d, x, y) * (13 - b) / w;
	if (c < 13)
		ans += dp(a, b, c + 1, d, x, y) * (13 - c) / w;
	if (d < 13)
		ans += dp(a, b, c, d + 1, x, y) * (13 - d) / w;
	if (!x)
		ans += std::min({dp(a, b, c, d, 1, y), dp(a, b, c, d, 2, y), dp(a, b, c, d, 3, y), dp(a, b, c, d, 4, y)}) / w;
	if (!y)
		ans += std::min({dp(a, b, c, d, x, 1), dp(a, b, c, d, x, 2), dp(a, b, c, d, x, 3), dp(a, b, c, d, x, 4)}) / w;
	return ++ans;
}

void solve(int T) {
	std::cin >> ia >> ib >> ic >> id;
	double ans = dp(0, 0, 0, 0, 0, 0);
	std::cout << std::fixed << std::setprecision(3);
	if (ans > 100)
		std::cout
			<< "Case " << T << ": "
			<< "-1.000\n";
	else
		std::cout
			<< "Case " << T << ": "
			<< ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	for (int i = 1; i <= t; i++) {
		init();
		solve(i);
	}
	return 0;
}
