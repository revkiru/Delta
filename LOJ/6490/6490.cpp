#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr i64 inf = 0x7f7f7f7f;

int n, ql, qr;
int a[N];
i64 s[N], f[N];

struct SparseTable {
	int lg2[N];
	i64 rmax[20][N], rmin[20][N];
	
	void init() {
		for (int i = 2; i <= n; i++)
			lg2[i] = lg2[i >> 1] + 1;
		for (int i = 1; i <= n; i++)
			rmax[0][i] = rmin[0][i] = s[i];
		for (int i = 1; (1 << i) <= n; i++) {
			for (int j = 0; j <= n - (1 << i) + 1; j++) {
				rmax[i][j] = std::max(rmax[i - 1][j], rmax[i - 1][j + (1 << (i - 1))]);
				rmin[i][j] = std::min(rmin[i - 1][j], rmin[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	
	i64 query_max(int l, int r) {
		if (l > r) return -inf;
		int x = lg2[r - l + 1];
		// int x = std::__lg(r - l + 1);
		return std::max(rmax[x][l], rmax[x][r - (1 << x) + 1]);
	}
	
	i64 query_min(int l, int r) {
		if (l > r) return inf;
		int x = lg2[r - l + 1];
		// int x = std::__lg(r - l + 1);
		return std::min(rmin[x][l], rmin[x][r - (1 << x) + 1]);
	}
} st;

void solve(int l, int r) {
	// std::cerr << l << " " << r << "\n";
	if (r - l + 1 < ql) { return; }
	if (l == r && ql == 1) { f[l] = std::max(f[l], 1ll * a[l]); return; }
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	
	i64 mx = -inf;
	for (int i = l; i <= mid; i++) {
		int lft = std::max(mid + 1, i + ql - 1);
		int rgt = std::min(r, i + qr - 1);
		mx = std::max(mx, st.query_max(lft, rgt) - s[i - 1]);
		// std::cerr << mx << "\n";
		f[i] = std::max(f[i], mx);
	}
	mx = -inf;
	for (int i = r; i >= mid + 1; i--) {
		int lft = std::max(l - 1, i - qr);
		int rgt = std::min(mid, i - ql);
		mx = std::max(mx, s[i] - st.query_min(lft, rgt));
		// std::cerr << mx << "\n";
		f[i] = std::max(f[i], mx);
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> ql >> qr;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		s[i] = s[i - 1] + a[i];
		f[i] = -inf;
	}
	st.init();
	solve(1, n);
	for (int i = 1; i <= n; i++)
		std::cout << f[i] << " ";
	std::cout << "\n";
	return 0;
}
