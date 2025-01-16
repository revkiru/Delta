#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int L = (1 << 22) + 1;
constexpr int P = 1e9 + 7;

int n, m;
int pw2[N], sum[L], f[L];

int ModAdd(const int x) { return x >= P ? x - P : x; }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	pw2[0] = 1;
	for (int i = 1; i <= n; i++)
		pw2[i] = ModAdd(pw2[i - 1] * 2);

	int U = (1 << m) - 1;
	for (int i = 1, k, v; i <= n; i++) {
		v = 0;
		std::cin >> k;
		for (int o; k; k--) {
			std::cin >> o;
			v |= 1 << (o - 1);
		}
		sum[v]++;
	}

	int _U = (1 << (m - 1)) - 1;
	for (int i = 0; i < m; i++) {
		int res = (1 << i) - 1;
		for (int s = 0; s <= _U; s++) {
			int s0 = (s & res) | ((s & (~res)) << 1);
			int s1 = s0 | (1 << i);
			sum[s1] += sum[s0];
		}
	}

	f[0] = 1;
	for (int s = 1; s <= U; s++)
		f[s] = ModAdd(-f[s ^ (s & (-s))] + P);

	int ans = 0;
	for (int s = 0; s <= U; s++)
		ans = ModAdd(ans + 1ll * f[s] * pw2[sum[s ^ U]] % P);
	std::cout << ans << "\n";
	return 0;
}
