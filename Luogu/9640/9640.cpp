#include <bits/stdc++.h>

#define int long long

constexpr int N = 157;
constexpr int P = 1e9 + 7;

int len, res, ret, mx, cur;
int fac[N], inv[N];
int dig[N], occ[N], f[N];

std::string s;

template <typename T>
T expow(T a, T b) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % P;
		a = a * a % P;
	}
	return ret;
}

void init(const int R) {
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= R; i++) {
		fac[i] = fac[i - 1] * i % P;
	}
	inv[0] = 1, inv[R] = expow(fac[R], P - 2);
	for (int i = R - 1; i; i--) {
		inv[i] = inv[i + 1] * (i + 1) % P;
	}
}

int dfs(int rem, int o, int m) {
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for (int i = 0; i <= 9; i++) {
		if (i == m)
			continue;
		if ((mx = o - (i > m) - occ[i]) < 0)
			return 0;
		for (int j = rem; j; j--) {
			for (int k = 1; k <= mx && k <= j; k++)
				f[j] = (f[j] + f[j - k] * inv[k]) % P;
		}
	}
	return f[rem];
}

void solve() {
	std::cin >> s;
	len = s.size(), res = 0;
	// std::cout << len << "!!!\n";
	s = '$' + s;

	auto calc = [&](int l, int r) -> int {
		int cot = 0;
		for (int i = 0; i <= 9; i++) {
			occ[i] = 0;
		}
		for (int i = 1; i < l; i++) {
			occ[dig[i]]++;
		}
		for (int i = 1; i <= 9; i++) {
			for (int j = occ[i]; j <= occ[i] + r - l + 1; j++) {
				ret = r - l + 1 - (j - occ[i]);
				cur = (((dfs(ret, j, i) * fac[r - l + 1]) % P) * inv[j - occ[i]]) % P;
				cot = (cot + i * cur) % P;
			}
		}
		return cot;
	};

	for (int i = 1; i < len; i++) {
		for (int j = 1; j <= 9; j++) {
			dig[1] = j;
			res = (res + calc(2, i)) % P;
		}
	}
	for (int i = 1; i <= len; i++) {
		dig[i] = 0;
		for (int j = (i == 1); j <= (s[i] - '1'); j++) {
			dig[i] = j;
			res = (res + calc(i + 1, len)) % P;
		}
		dig[i] = s[i] - '0';
	}
	res = (res + calc(len + 1, len)) % P;
	std::cout << res << "\n";
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init(100);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
