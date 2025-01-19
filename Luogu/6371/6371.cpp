#include <bits/stdc++.h>

#define int long long

constexpr int N = 20;

int d, l, r, mxn, a[N];
bool cnt[N];
std::string str;
std::map<int, int> f[N];

int dfs(int pos, int lim, int flg, int num) {
	if (!pos) { return num == 0 ? 1 : 0; }
	if (!lim && !flg && f[pos].count(num)) { return f[pos][num]; }
	int u = lim ? a[pos] : 9, res = 0, t = num, ret = 0;
	for (int i = 1; i <= pos; i++) { t = t * 10ll % d; }
	ret = ((d - t) % d + d) % d;
	t = 0;
	for (int i = 1; i <= pos; i++) { t = t * 10ll + mxn; }
	if (t < ret) {
		if (!lim && !flg) f[pos][num] = res;
		return res;
	}
	for (int i = 0; i <= u; i++) {
		if (cnt[i] || (i == 0 && flg))
			res += dfs(pos - 1, lim && i == u, flg && i == 0, (num * 10ll + i) % d);
	}
	if (!lim && !flg) f[pos][num] = res;
	return res;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> d >> l >> r;
	std::cin >> str;
	int n = str.size();
	for (int i = 0; i < n; i++) {
		cnt[str[i] - '0'] = 1;
		mxn = std::max(mxn, (int) (str[i] - '0'));
	}

	auto solve = [&](int x) -> int {
		int p = 0;
		for (; x; x /= 10)
			a[++p] = x % 10;
		return dfs(p, 1, 1, 0);
	};
	std::cout << solve(r) - solve(l - 1) << "\n";
	return 0;
}
