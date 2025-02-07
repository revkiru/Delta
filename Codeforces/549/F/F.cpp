#include <bits/stdc++.h>

#define int long long

constexpr int N = 3e5 + 7;

int n, k, ans;
int a[N], s[N];
std::map<int, int> mp;

template <typename T>
T MyMod(T x) { return (x >= k ? x -= k : x); }

struct RMQ {
	std::pair<int, int> f[20][N];

	void init() {
		for (int i = 1; i <= n; i++)
			f[0][i] = {a[i], i};
		for (int j = 1; j <= std::__lg(n); j++) {
			for (int i = 1; i + (1 << j) - 1 <= n; i++)
				f[j][i] = std::max(f[j - 1][i], f[j - 1][i + (1 << j - 1)]);
		}
	}

	std::pair<int, int> queryMax(int l, int r) {
		int x = std::__lg(r - l + 1);
		return std::max(f[x][l], f[x][r - (1 << x) + 1]);
	}
} tab;

void solve(int l, int r, int d) {
	if (l >= r) { ans += (l == r); return; }
	auto [mx, p] = tab.queryMax(l, r);
	mx %= k;
	if (p - l <= r - p) {
		for (int i = l; i < p; i++)
			mp[s[i]]--;
		for (int i = l; i <= p; i++)
			ans += mp[MyMod(s[i - 1] + mx)];
		mp[s[p]]--;
		solve(p + 1, r, d + 1);
		mp.clear();
		for (int i = l; i < p; i++)
			mp[s[i]]++;
		solve(l, p - 1, d + 1);
	} else {
		for (int i = p + 1; i <= r; i++)
			mp[s[i]]--;
		mp[s[l - 1]]++, mp[s[p]]--;
		for (int i = p; i <= r; i++)
			ans += mp[MyMod(s[i] - mx + k)];
		mp[s[l - 1]]--;
		solve(l, p - 1, d + 1);
		mp.clear();
		for (int i = p + 1; i <= r; i++)
			mp[s[i]]++;
		solve(p + 1, r, d + 1);
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		MyMod(s[i] = s[i - 1] + a[i] % k);
		mp[s[i]]++;
	}
	tab.init();
	solve(1, n, 0);
	std::cout << ans - n << "\n";
	return 0;
}
