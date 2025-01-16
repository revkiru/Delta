#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 5e4 + 7;

int n, tim, ans;

struct node {
	int t1, t2;

	bool operator < (const node &rhs) const {
		return t2 < rhs.t2;
	};
} a[N];

std::priority_queue<int> q;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i].t1 >> a[i].t2;
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		tim += a[i].t1;
		q.push(a[i].t1);
		if (tim <= a[i].t2) {
			ans++;
		} else {
			tim -= q.top();
			q.pop();
		}
	}
	std::cout << ans << "\n";
	return 0;
}
