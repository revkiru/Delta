#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;

int n, k, t;
int x[N];
int b[N];

bool check(int v) {
	for (int i = 1; i <= n; i++)
		b[i] = x[i] - 2 * t * v * i;
	if (b[1] < b[n]) return 0;
	
	int L = k, R = k;
	for (int i = k - 1; i >= 1; i--)
		if (b[i] >= b[L])
			L = i;
	for (int i = k + 1; i <= n; i++)
		if (b[i] <= b[R])
			R = i;
	
	int l = k, r = k;
	while (L < l || r < R) {
		bool flg0 = 0, flg1 = 0;
		int nl = l, nr = r;
		while (nl > L && b[nl - 1] >= b[r]) {
			if (b[--nl] >= b[l]) { flg1 = 1; break; }
		}
		if (flg1) { flg0 = 1; l = nl; }
		flg1 = 0;
		while (nr < R && b[nr + 1] <= b[l]) {
			if (b[++nr] <= b[r]) { flg1 = 1; break; }
		}
		if (flg1) { flg0 = 1; r = nr; }
		if (!flg0) return 0;
	}
	
	l = 1, r = n;
	while (l < L || R < r) {
		bool flg0 = 0, flg1 = 0;
		int nl = l, nr = r;
		while (nl < L && b[nl + 1] >= b[r]) {
			if (b[++nl] >= b[l]) { flg1 = 1; break; }
		}
		if (flg1) { flg0 = 1; l = nl; }
		flg1 = 0;
		while (nr > R && b[nr - 1] <= b[l]) {
			if (b[--nr] <= b[r]) { flg1 = 1; break; }
		}
		if (flg1) { flg0 = 1; r = nr; }
		if (!flg0) return 0;
	}
	return 1;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> k >> t;
	for (int i = 1; i <= n; i++)
		std::cin >> x[i];
	
	int l = 0, r = x[n] / t + 1;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid;
		else l = mid + 1;
	}
	if (check(0)) r = 0;
	std::cout << r << "\n";
	return 0;
}
