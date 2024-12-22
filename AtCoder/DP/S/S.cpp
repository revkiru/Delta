#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int D = 107;
constexpr int P = 1e9 + 7;

int n, d;
int num[N], dp[N][D][2];
std::string s;

int dfs(int u, int x, int lim) {
	if (!u) { return (x == 0); }
	if (~dp[u][x][lim]) { return dp[u][x][lim]; }
	int ret = 0, mx = 9;
	if (lim) { mx = num[u]; }
	for (int i = 0; i <= mx; i++)
		ret = (ret + dfs(u - 1, (x + i) % d, lim && (i == mx))) % P;
	return dp[u][x][lim] = ret;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> s >> d;
	n = s.size();
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++)
		num[i + 1] = s[n - i - 1] - '0';
	std::cout << (dfs(n, 0, 1) - 1 % P + P) % P << "\n";
	return 0;
}
