#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int a[N], b[N];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= n; i++)
		std::cin >> b[i];
	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + n + 1);

	auto solve = [&](int a[], int b[]) -> int {
		int l1 = 1, r1 = n, l2 = 1, r2 = n;
		int res = 0;
		while (l1 <= r1 && l2 <= r2) {
			if (a[l1] > b[l2]) {
				res += 2;
				l1++, l2++;
			} else if (a[r1] > b[r2]) {
				res += 2;
				r1--, r2--;
			} else {
				res += (a[l1] == b[r2]);
				l1++, r2--;
			}
		}
		return res;
	};

	std::cout << solve(a, b) << " " << 2 * n - solve(b, a) << "\n";
	return 0;
}
