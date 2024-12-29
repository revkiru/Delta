#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, q;
int a[N], sum[N], ans[N];

struct ques {
	int l, r, id;

	bool operator < (const ques &other) const {
		return r < other.r;
	}
} qs[N];

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= q; i++) {
		std::cin >> qs[i].l >> qs[i].r;
		qs[i].id = i;
	}

	std::sort(qs + 1, qs + q + 1);

	int cur1 = 1, cur2 = 0;
	for (int i = 1; i <= q; i++) {
		while (cur1 <= qs[i].r) {
			if (a[cur1] > 0) {
				cur2 = cur1 - 1;
				int ret = 0, cnt = 1;
				while (cur2 && a[cur2] <= 0 && std::abs(ret + a[cur2]) < a[cur1]) {
					ret += a[cur2];
					cur2--;
					cnt++;
				}
				for (int i = cur1 - cnt + 1; i <= cur1; i++)
					sum[i] = sum[i - 1] + 1;
			} else {
				sum[cur1] = sum[cur1 - 1];
			}
			cur1++;
		}
		ans[qs[i].id] = sum[qs[i].r] - sum[qs[i].l - 1];
	}

	for (int i = 1; i <= q; i++)
		std::cout << ans[i] << "\n";
	return 0;
}
