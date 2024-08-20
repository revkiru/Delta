#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int t, n, k;
int a[N];

void solve(int trn) {
	if (trn == 1) {
		std::cin >> n;
		for (int i = 1; i <= n; i++)
			std::cin >> a[i];
	} else {
		std::cin >> k;
		for (int i = 1; i <= k; i++) {
			int x, y;
			std::cin >> x >> y;
			a[x] = y;
		}
	}
	
	std::deque<std::pair<int, int>> q1, q2;
	for (int i = 1; i <= n; i++)
		q1.push_back({a[i], i});

	int ans;
	while (1) {
		if (q1.size() + q2.size() == 2) { ans = 1; break; }
		int x, y, id;
		y = q1.front().first;
		q1.pop_front();
		if (q2.empty() || (!q1.empty() && q1.back() > q2.back())) {
			x = q1.back().first, id = q1.back().second;
			q1.pop_back();
		} else {
			x = q2.back().first, id = q2.back().second;
			q2.pop_back();
		}
		
		std::pair<int, int> u = {x - y, id};
		if (q1.empty() || q1.front() > u) {
			ans = q1.size() + q2.size() + 2;	// not eat
			int cot = 0;
			while (1)  {
				cot++;
				if (q1.size() + q2.size() + 1 == 2) {
					if (cot % 2 == 0)
						ans--;
					break;
				}
				int x, id;
				if (q2.empty() || (!q1.empty() && q1.back() > q2.back())) {
					x = q1.back().first, id = q1.back().second;
					q1.pop_back();
				} else {
					x = q2.back().first, id = q2.back().second;
					q2.pop_back();
				}
				u = {x - u.first, id};
				if ((q1.empty() || u < q1.front()) && (q2.empty() || u < q2.front())) { ; }
				else {
					if (cot % 2 == 0)
						ans--;
					break;
				}
			}
			break;
		} else {
			q2.push_front(u);
		}
	}
	
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	// freopen("snakes.in", "r", stdin);
	// freopen("snakes.out", "w", stdout);

	std::cin >> t;
	for (int i = 1; i <= t; i++) {
		solve(i);
	}
	return 0;
}
