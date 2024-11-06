#include <bits/stdc++.h>

using i64 = long long;

void solve() {
	int n;
	std::string s;
	std::cin >> n >> s;
	int cnt = 1;
	std::vector<int> a(n + 1);
	if (s[0] == '=')
		cnt = 2;
	else
		a[1] = 1;

	char lst = s[0];
	for (int i = 1; i < n - 1; i++) {
		if (s[i] == '=') {
			a[i + 1] = a[i];
			cnt++;
		}
		else if (s[i] == s[i - 1]) {
			a[i + 1] = a[i] + 1;
			cnt = 1;
		}
		else if (s[i] != lst) {
			a[i + 1] = cnt;
			cnt = 1;
			lst = s[i];
		}
		else if (s[i] == lst) {
			a[i + 1] = a[i] + cnt;
			cnt = 1;
		}
	}
	i64 ans = 0;
	for (int i = 0; i <= n; i++)
		ans += a[i];
	std::cout << ans << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
