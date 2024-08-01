#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, siz;
int bid[N];
i64 a[N], lzy[N];

void add(int l, int r, i64 c) {
	int sid = bid[l], eid = bid[r];
	if (sid == eid) {
		for (int i = l; i <= r; i++)
			a[i] += c;
		return;
	}
	for (int i = l; bid[i] == sid; i++) { a[i] += c; }
	for (int i = sid + 1; i < eid; i++) { lzy[i] += c; }
	for (int i = r; bid[i] == eid; i--) { a[i] += c; }
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	siz = std::sqrt(n);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		bid[i] = (i - 1) / siz + 1;
	}
	for (int i = 1; i <= n; i++) {
		int opt, l, r;
		i64 c;
		std::cin >> opt >> l >> r >> c;
		if (opt == 0) {
			add(l, r, c);
		} else {
			std::cout << a[r] + lzy[bid[r]] << "\n";
		}
	}
	return 0;
}
