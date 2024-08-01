#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, siz, bid[N];
i64 a[N], s[N], lzy[N];

void add(int l, int r, i64 c) {
	int sid = bid[l], eid = bid[r];
	if (sid == eid) {
		for (int i = l; i <= r; i++) { a[i] += c; s[sid] += c; }
		return;
	}

	for (int i = l; bid[i] == sid; i++) { a[i] += c; s[sid] += c; }
	for (int i = sid + 1; i < eid; i++) { lzy[i] += c; s[i] += siz * c; }
	for (int i = r; bid[i] == eid; i--) { a[i] += c; s[eid] += c; }
}

i64 query(int l, int r, i64 c) {
	const int P = c + 1;
	int sid = bid[l], eid = bid[r];
	i64 res = 0;
	if (sid == eid) {
		for (int i = l; i <= r; i++)
			(res += (a[i] + lzy[sid]) % P) %= P;
		return res % P;
	}

	for (int i = l; bid[i] == sid; i++) { (res += (a[i] + lzy[sid]) % P) %= P; }
	for (int i = sid + 1; i < eid; i++) { (res += (s[i] % P)) %= P; }
	for (int i = r; bid[i] == eid; i--) { (res += (a[i] + lzy[eid]) % P) %= P; }
	return res;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	siz = std::sqrt(n);
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		bid[i] = (i - 1) / siz + 1;
		s[bid[i]] += a[i];
	}
	for (int i = 1; i <= n; i++) {
		int opt, l, r;
		i64 c;
		std::cin >> opt >> l >> r >> c;
		if (opt == 0) {
			add(l, r, c);
		} else {
			std::cout << query(l, r, c) << "\n";
		}
	}
	return 0;
}
