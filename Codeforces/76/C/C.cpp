#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int K = 25;

int n, k, _t, U;
std::string s;
int can[K], t[K], a[K][K];
int f[1 << K];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k >> _t >> s;
	for (int i = 0; i < n; i++) {
		s[i] -= 'A';
		U |= (1 << s[i]);
	}
	for (int i = 0; i < k; i++)
		std::cin >> t[i];
	for (int i = 0; i < k; i++)
		for (int j = 0; j < k; j++)
			std::cin >> a[i][j];

	memset(can, -1, sizeof(can));
	for (int i = 0; i < k; i++)
		f[1 << i] = t[i];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < k; j++) {
			if (can[j] >= 0) {
				if (!((can[j] >> j) & 1) && !((can[j] >> s[i]) & 1)) {
					f[can[j]] += a[j][s[i]];
					f[can[j] | (1 << j)] -= a[j][s[i]];
					f[can[j] | (1 << s[i])] -= a[j][s[i]];
					f[can[j] | (1 << j) | (1 << s[i])] += a[j][s[i]];
				}
				can[j] |= (1 << s[i]);
			}
		}
		can[s[i]] = 0;
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < (1 << k); j++)
			if ((j >> i) & 1)
				f[j] += f[j ^ (1 << i)];
	}

	int ans = 0;
	for (int i = 0; i < (1 << k); i++)
		if ((i & U) == i && f[i] <= _t && i != U)
			ans++;
	std::cout << ans << "\n";
	return 0;
}

/* 神仙容斥 */
