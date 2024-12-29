#include <bits/stdc++.h>

#define int long long

constexpr int N = 3e5 + 7;
constexpr int P = 1e9 + 7;

int n, h, w;
int dp[N], inv[N], fac[N];

std::pair<int, int> p[N];

template <typename T>
T expow(T a, T b, const T P) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % P;
		a = a * a % P;
	}
	return ret % P;
}

int C(int x, int y) {
	return (fac[x] * inv[y] % P) * inv[x - y] % P;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> h >> w >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> p[i].first >> p[i].second;
	p[n + 1].first = h, p[n + 1].second = w;
	std::sort(p + 1, p + n + 1);

	inv[0] = fac[0] = 1;
	for (int i = 1; i < (int) 3e5; i++) {
		fac[i] = (fac[i - 1] * i) % P;
		inv[i] = expow(fac[i], P - 2, P);
	}

	dp[0] = 1;
	p[0].first = p[0].second = 1;
	for (int i = 1; i <= n + 1; i++) {
		dp[i] = C(p[i].first + p[i].second - 2, p[i].first - 1) % P;
		for (int j = 1; j < i; j++) {
			if (p[j].first > p[i].first || p[j].second > p[i].second)
				continue;
			int dx = p[i].first - p[j].first, dy = p[i].second - p[j].second;
			dp[i] -= dp[j] * C(dx + dy, dx) % P;
			dp[i] = (dp[i] + P) % P;
		}
	}
	std::cout << dp[n + 1] % P << "\n";
	return 0;
}
