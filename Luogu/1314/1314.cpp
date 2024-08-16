#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, m;
i64 W, S, ql, qr;
i64 l[N], r[N];
i64 sw[N], sv[N], w[N], v[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m >> S;
	W = S;
	i64 x = 1, y = w[1];
	for (int i = 1; i <= n; i++) {
		std::cin >> w[i] >> v[i];
		y = std::max(y, w[i]);
	}
	y++;
	for (int i = 1; i <= m; i++)
		std::cin >> l[i] >> r[i];

	i64 sum, mid;
	while (x < y) {
		mid = (x + y) >> 1, sum = 0;
		for (int i = 0; i <= n; i++)
			sw[i] = sv[i] = 0;
		for (int i = 1; i <= n; i++) {
			sw[i] = sw[i - 1];
			sv[i] = sv[i - 1];
			if (w[i] >= mid) {
				sw[i] += 1;
				sv[i] += v[i];
			}
		}
		
		for (int i = 1; i <= m; i++) {
			sum += (sw[r[i]] - sw[l[i] - 1]) * (sv[r[i]] - sv[l[i] - 1]);
		}
		
		if (sum == S) { W = 0; break; }
		W = std::min(W, std::abs(sum - S));
		
		if (sum <= S) y = mid;
		else x = mid + 1;
	}
	std::cout << W << "\n";
	return 0;
}
