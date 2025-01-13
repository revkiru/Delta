#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;
constexpr int inf = 1e18;

int n, ans, tl, tr;
int l[N], r[N], len[N];
std::priority_queue<int> q1, q2;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> l[i] >> r[i];
		len[i] = r[i] - l[i];
		if (i == 1) {
			q1.push(l[i]), q2.push(-l[i]);
			q1.push(-inf), q2.push(-inf);
			continue;
		}

		tl += len[i], tr += len[i - 1];
		if (l[i] < q1.top() - tl) {
			int x = q1.top() - tl;
			q1.pop();
			ans += x - l[i];
			q1.push(l[i] + tl);
			q1.push(l[i] + tl);
			q2.push(-x + tr);
		} else if (l[i] <= -q2.top() + tr) {
			q1.push(l[i] + tl);
			q2.push(-l[i] + tr);
		} else {
			int x = -q2.top() + tr;
			q2.pop();
			ans += l[i] - x;
			q2.push(-l[i] + tr);
			q2.push(-l[i] + tr);
			q1.push(x + tl);
		}
	}
	std::cout << ans << "\n";
	return 0;
}
