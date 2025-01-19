#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 77;
constexpr int L = 2507;
constexpr int inf = 0x3f3f3f3f;

int n, sum;
std::pair<int, int> dat[N];
int lsum[N], lst[L][L], f[L][L];

void chkmax(int &a, int b) { a = std::min(a, b); }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> dat[i].first >> dat[i].second;
		dat[i].first *= -1;
		sum += dat[i].second;
	}
	std::sort(dat + 1, dat + n + 1);
	for (int i = 1; i <= n; i++)
		dat[i].first *= -1;
	for (int i = 1; i <= n; i++)
		lsum[i] = lsum[i - 1] + dat[i].second;

	memset(lst, 0x3f, sizeof(0x3f));
	memset(f, 0x3f, sizeof(f));
	lst[0][0] = 0;
	for (int i = 1; i <= n; i++) {
		int h = dat[i].first, l = dat[i].second, s = lsum[i - 1];
		for (int a = 0; a <= s; a++) {
			for (int b = 0; a + b <= s; b++) {
				if (lst[a][b] != inf) {
					if (!a) chkmax(f[l][b], lst[0][b] + h);
					else chkmax(f[a + l][b], lst[a][b]);
					if (!b) chkmax(f[a][l], lst[a][0] + h);
					else chkmax(f[a][b + l], lst[a][b]);
					if (!(s - a - b)) chkmax(f[a][b], lst[a][b] + h);
					else chkmax(f[a][b], lst[a][b]);
				}
			}
		}
		memcpy(lst, f, sizeof(f));
		memset(f, 0x3f, sizeof(f));
	}

	int ans = inf;
	for (int a = 1; a <= sum; a++) {
		for (int b = 1; b <= sum; b++) {
			if (sum - a - b)
				if (lst[a][b] != inf)
					if (ans > std::max({a, b, sum - a - b}) * lst[a][b])
						ans = std::max({a, b, sum - a - b}) * lst[a][b];
		}
	}

	std::cout << ans << "\n";
	return 0;
}
