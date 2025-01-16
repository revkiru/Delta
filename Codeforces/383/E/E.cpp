#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e4 + 7;
constexpr int L = (1 << 24) + 1;

int n, ans;
int f[L];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		int res = 0;
		char ch;
		for (int j = 1; j <= 3; j++) {
			std::cin >> ch;
			res = res | (1 << (ch - 'a'));
		}
		f[res]++;
	}
	for (int i = 0; i < 24; i++) {
		for (int j = 0; j < (1 << 24); j++)
			if (j & (1 << i))
				f[j] += f[j ^ (1 << i)];
	}
	for (int i = 0; i < (1 << 24); i++)
		ans ^= (n - f[i]) * (n - f[i]);
	std::cout << ans << "\n";
	return 0;
}

/* 正难则反，考虑维护辅音字母集合 */
