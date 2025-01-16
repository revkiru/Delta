#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int L = (1 << 22) + 1;

int n, m;
int num[L], f[L][2];
std::pair<int, int> a[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y;
		std::cin >> x >> y;
		a[i] = {x, y};
	}
	std::sort(a + 1, a + m + 1);
	i64 ans = 0;

	for (int j = 0; j <= 30; j++) {
		int cot = 0;
		if (a[1].first > 1) num[++cot] = 2;

		if (a[1].second & (1 << j)) num[++cot] = 1;
		else num[++cot] = 0;

		for (int i = 2; i <= m; i++) {
			if (a[i].first - a[i - 1].first >= 3) {
				num[++cot] = 2;
				num[++cot] = 2;
			} else if (a[i].first - a[i - 1].first == 2) {
				num[++cot] = 2;
			}

			if (a[i].second & (1 << j)) num[++cot] = 1;
			else num[++cot] = 0;
		}
		if (a[m].first < n)
			num[++cot] = 2;

		memset(f, 0x3f, sizeof(f));
		if (num[1] == 0) f[1][0] = 0;
		else if (num[1] == 1) f[1][1] = 1;
		else if (num[1] == 2) { f[1][0] = 0; f[1][1] = 1; }

		for (int i = 2; i <= cot; i++) {
			if (num[i] == 0) {
				f[i][0] = f[i - 1][0];
				f[i][1] = f[i - 1][1] + 1;
			} else if (num[i] == 1) {
				f[i][0] = f[i - 1][1];
				f[i][1] = f[i - 1][0] + 1;
			} else if (num[i] == 2) {
				f[i][0] = std::min(f[i - 1][0], f[i - 1][1]);
				f[i][1] = std::min(f[i - 1][0], f[i - 1][1]) + 1;
			}
		}
		ans += 1ll * std::min(f[cot][0], f[cot][1]) * (1 << j);
	}

	std::cout << ans << "\n";
	return 0;
}

/* 按位贪心 DP */
