#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 207;

int n, m;
int sgf[N][N];

int SG(int x, int y) {
	bool f[N] = {0};
	if (sgf[x][y] != -1)
		return sgf[x][y];
	for (int i = 2; i <= x - i; i++)
		f[SG(i, y) ^ SG(x - i, y)] = 1;
	for (int i = 2; i <= y - i; i++)
		f[SG(x, i) ^ SG(x, y - i)] = 1;
	
	int t = 0;
	while (f[t])
		t++;
	return sgf[x][y] = t;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	memset(sgf, -1, sizeof(sgf));
	sgf[2][2] = sgf[2][3] = sgf[3][2] = 0;

	while (std::cin >> n >> m)
		std::cout << (SG(n, m) ? "WIN" : "LOSE") << "\n";
	return 0;
}
