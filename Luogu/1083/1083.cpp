#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n, m;
int r[N], d[N], s[N];
i64 t[N], dif[N], sum[N];

bool check(i64 x) {
	memset(dif, 0, sizeof(dif));
	for (i64 i = 1; i <= x; i++) {
		dif[s[i]] += d[i];
		dif[t[i] + 1] -= d[i];
	}
	for (i64 i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + dif[i];
		if (sum[i] > r[i])
			return 0;
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> r[i];
	for (int i = 1; i <= m; i++)
		std::cin >> d[i] >> s[i] >> t[i];
	
	i64 _l = 1, _r = m;
	if (check(m)) { std::cout << "0\n"; exit(0); }
	
	while (_l < _r) {
		i64 mid = (_l + _r) >> 1;
		if (check(mid)) _l = mid + 1;
		else _r = mid;
	}
	std::cout << "-1\n" << _l << "\n";
	return 0;
}
