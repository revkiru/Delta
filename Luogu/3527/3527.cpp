#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n, m, k, bsiz;
int a[N], p[N];
int bid[N], siz[N], bel[N], ans[N];
i64 sum[N], pf[N], res[N];

std::vector<int> vec[N];

struct ques {
	int l, r, k;
} q[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, x; i <= m; i++) {
		std::cin >> x;
		vec[x].push_back(i);
		siz[x]++;
		bel[i] = x;
	}
	for (int i = 1; i <= n; i++)
		std::cin >> p[i];
	std::cin >> k;

	bsiz = std::sqrt(k) * 2.5;
	for (int i = 1; i <= (k - 1) / bsiz + 1; i++) {
		int l = (i - 1) * bsiz + 1, r = std::min(k, i * bsiz);
		for (int j = l; j <= r; j++) {
			std::cin >> q[j].l >> q[j].r >> q[j].k;
			if (q[j].l > q[j].r) {
				sum[q[j].l] += q[j].k;
				sum[m + 1] -= q[j].k;
				sum[1] += q[j].k;
				sum[q[j].r + 1] -= q[j].k;
			} else {
				sum[q[j].l] += q[j].k;
				sum[q[j].r + 1] -= q[j].k;
			}
		}
		for (int j = 1; j <= m; j++) {
			pf[j] = sum[j] + pf[j - 1];
			res[bel[j]] += pf[j];
		}
		for (int u = 1; u <= n; u++) {
			i64 np = res[u];
			if (ans[u] || np < p[u])
				continue;
			for (int j = r; j >= l; j--) {
				for (int _x = 0; _x < siz[u]; _x++) {
					if (q[j].l <= q[j].r) {
						if (q[j].l <= vec[u][_x] && vec[u][_x] <= q[j].r)
							np -= q[j].k;
					} else {
						if (q[j].l <= vec[u][_x] || vec[u][_x] <= q[j].r)
							np -= q[j].k;
					}
				}
				if (np < p[u]) {
					ans[u] = j;
					break;
				}
			}
		}
		memset(res, 0, sizeof(res));
	}

	for (int i = 1; i <= n; i++) {
		if (ans[i] == 0)
			std::cout << "NIE\n";
		else
			std::cout << ans[i] << "\n";
	}
	return 0;
}
