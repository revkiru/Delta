#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int L = 1e6 + 7;
constexpr int M = 46340;
constexpr int inf = 0x7f7f7f7f;

bool v[L];
std::vector<int> p, ans;

void init() {
	memset(v, 1, sizeof(v));
	for (int i = 2; i <= M; i++) {
		if (v[i]) {
			p.push_back(i);
			for (int j = 2; j <= (M / i); j++)
				v[i * j] = 0;
		}
	}
}

void solve(i64 l, i64 r) {
	memset(v, 1, sizeof(v));
	ans.clear();
	if (l == 1)
		v[0] = 0;
	for (i64 i = 0; i < p.size(); i++) {
		for (i64 j = (l - 1) / p[i] + 1; j <= (r / p[i]); j++)
			if (j > 1)
				v[p[i] * j - l] = 0;
	}
	for (i64 i = l; i <= r; i++)
		if (v[i - l])
			ans.push_back(i);
	int mn = inf, mx = -inf;
	int _x1, _x2, _y1, _y2;
	for (i64 i = 0; i + 1 < ans.size(); i++) {
		int num = ans[i + 1] - ans[i];
		if (num < mn) {
			mn = num;
			_x1 = ans[i];
			_y1 = ans[i + 1];
		}
		if (num > mx) {
			mx = num;
			_x2 = ans[i];
			_y2 = ans[i + 1];
		}
	}
	if (mx == -inf) {
		std::cout << "There are no adjacent primes.\n";
	} else {
		std::cout << _x1 << "," << _y1 << " are closest, " << _x2 << "," << _y2 << " are most distant.\n";
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();
	i64 l, r;
	while (std::cin >> l >> r) {
		solve(l, r);
	}
	return 0;
}
