#include <bits/stdc++.h>

#define int long long

constexpr int N = 507;
constexpr int M = 1e6 + 7;
constexpr int P = 1e9 + 7;

int n, k, top;
int h[N], ls[N], rs[N], stc[N];
int fac[M], inv[M];
int siz[N], g[N], dp[N][N];

template <typename T>
T expow(T a, T b, const T P) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % P;
		a = a * a % P;
	}
	return ret;
}

bool cmp(const int a, const int b) {
	return h[a] < h[b];
}

void preo(int o) {
	siz[o] = 1;
	if (ls[o]) { preo(ls[o]); siz[o] += siz[ls[o]]; }
	if (rs[o]) { preo(rs[o]); siz[o] += siz[rs[o]]; }
}

int A(const int n, const int m) {
	if (m > n) return 0;
	return fac[n] * inv[n - m] % P;
}

int calc(int n, int m, int k) {
	return A(n, k) * A(m, k) % P * inv[k] % P;
}

void dfs(int u, int low) {
	int nh = h[u] - low;
	if (!ls[u] && !rs[u]) {
		dp[u][0] = 1;
		for (int i = 1; i <= k; i++)
			dp[u][i] = calc(siz[u], nh, i);
		return;
	}
	if (!ls[u] || !rs[u]) {
		int v = (ls[u] ? ls[u] : rs[u]);
		dfs(v, h[u]);
		memset(g, 0, sizeof(g));
		g[0] = 1;
		for (int i = 1; i <= k; i++) {
			for (int j = 0; j <= i; j++)
				g[i] = (g[i] + dp[0][j] * dp[v][i - j]) % P;
		}
		dp[u][0] = 1;
		for (int i = 1; i <= k; i++)
			for (int j = 0; j <= i; j++)
				dp[u][i] = (dp[u][i] + g[j] * calc(nh, siz[u] - j, i - j)) % P;
		return;
	}
	dfs(ls[u], h[u]);
	dfs(rs[u], h[u]);
	memset(g, 0, sizeof(g));
	g[0] = 1;
	for (int i = 1; i <= k; i++)
		for (int j = 0; j <= i; j++)
			g[i] = (g[i] + dp[ls[u]][j] * dp[rs[u]][i - j]) % P;
	dp[u][0] = 1;
	for (int i = 1; i <= k; i++)
		for (int j = 0; j <= i; j++)
			dp[u][i] = (dp[u][i] + g[j] * calc(nh, siz[u] - j, i - j)) % P;
}

void init() {
	fac[0] = inv[0] = 1;
	for (int i = 1; i <= 1000000; i++) {
		fac[i] = fac[i - 1] * i % P;
		inv[i] = inv[i - 1] * expow(i, P - 2, P) % P;
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++)
		std::cin >> h[i];
	for (int i = 1; i <= n; i++) {
		int _k = top;
		while (_k && h[stc[_k]] > h[i])
			--_k;
		if (_k)
			rs[stc[_k]] = i;
		if (_k != top)
			ls[i] = stc[_k + 1];
		stc[top = ++_k] = i;
	}

	preo(stc[1]);
	dp[0][0] = 1;
	dfs(stc[1], 0);

	std::cout << dp[stc[1]][k] << "\n";
	return 0;
}
