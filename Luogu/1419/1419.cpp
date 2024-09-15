#include <bits/stdc++.h>

using i64 = long long;
using f64 = double;

constexpr int N = 1e5 + 7;
constexpr f64 eps = 1e-5;

int n, s, t;
int a[N];
double sum[N];

bool check(double mid) {
	for (int i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + (f64) a[i] - mid;
	std::deque<int> q;
	for (int i = s; i <= n; i++)  {
		while (!q.empty() && sum[q.back()] > sum[i - s])
			q.pop_back();
		q.push_back(i - s);
		while (!q.empty() && q.front() < i - t)
			q.pop_front();
		if (!q.empty() && sum[i] - sum[q.front()] > 0)
			return 1;
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	std::cin >> s >> t;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];

	double l = -N, r = N;
	while (l + eps < r) {
		double mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	std::cout << std::fixed << std::setprecision(3) <<  l << "\n";
	return 0;
}
