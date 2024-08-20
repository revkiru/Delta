#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3007;

int n, m, k;
int a, b, c;
int s[N];
i64 t, ans;
std::priority_queue<int, std::vector<int>, std::greater<int>> q;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> m >> k;
	std::cin >> a >> b >> c;
	std::cin >> t;
	for (int i = 1; i <= m; i++)
		std::cin >> s[i];
	s[m + 1] = n + 1;
	k -= m;
	for (int i = 1; i <= m; i++) {
		i64 ns = s[i], ret = t - 1ll * (s[i] - 1) * b;
		if (ret < 0)
			break;
		i64 u = s[i] + ret / a;
		ans += std::min(u, 1ll * s[i + 1] - 1) - s[i] + 1;
		int uk = k;
		while (uk && ret >= 0) {
			uk--;
			i64 nst = (u + 1 - ns) * c;
			ret -= nst;
			if (ret < 0)
				break;
			ns = u + 1;
			if (ns >= s[i + 1])
				break;
			u = ns + ret / a;
			q.push(std::min(u, 1ll * s[i + 1] - 1) - ns + 1);
			while ((int) q.size() > k)
				q.pop();
		}
	}
	while (!q.empty()) {
		ans += q.top();
		q.pop();
	}
	std::cout << ans - 1 << "\n";
	return 0;
}
