#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 50007;

int n, ansl, ansr;

struct line {
	int l, r;
} a[N];

bool cmp(const line &x, const line &y) { return x.l < y.l; }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i].l >> a[i].r;

	std::sort(a + 1, a + n + 1, cmp);
	ansl = a[1].l, ansr = a[1].r;
	for (int i = 2; i <= n; i++) {
		if (a[i].l > ansr) {
			std::cout << ansl << " " << ansr << "\n";
			ansl = a[i].l;
			ansr = std::max(ansr, a[i].r);
		} else {
			ansr = std::max(ansr, a[i].r);
		}
	}
	std::cout << ansl << " " << ansr << "\n";
	return 0;
}
