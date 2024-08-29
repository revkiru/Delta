#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr int P = 92084931;

int n, m, ans;
int a[N], b[N], s[N];

void _merge(int l, int mid, int r) {
	int p1 = l, p2 = mid + 1, k = l - 1;
	while (p1 <= mid && p2 <= r) {
		if (s[p1] < s[p2]) {
			(ans += (mid - p1 + 1)) %= P;
			b[++k] = s[p2];
			p2++;
		} else if (s[p1] >= s[p2]) {
			b[++k] = s[p1];
			p1++;
		}
	}
	while (p1 <= mid)
		b[++k] = s[p1++];
	while (p2 <= r)
		b[++k] = s[p2++];
	for (int i = l; i <= r; i++)
		s[i] = b[i];
}

void mergeSort(int l, int r) {
	if (l < r) {
		int mid = (l + r) >> 1;
		mergeSort(l, mid);
		mergeSort(mid + 1, r);
		_merge(l, mid, r);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		a[i] -= m;
		s[i] = s[i - 1] + a[i];
	}

	mergeSort(0, n);
	std::cout << ans << "\n";
	return 0;
}
