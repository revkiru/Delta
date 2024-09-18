#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, q;
int a[N];

struct SparseTable {
	int lg2[N], rmax[20][N], rmin[20][N];
	
	void init() {
		for (int i = 2; i <= n; i++)
			lg2[i] = lg2[i >> 1] + 1;
		for (int i = 1; i <= n; i++)
			rmax[0][i] = rmin[0][i] = a[i];
		for (int i = 1; (1 << i) <= n; i++) {
			for (int j = 1; j <= n - (1 << i) + 1; j++) {
				rmax[i][j] = std::max(rmax[i - 1][j], rmax[i - 1][j + (1 << (i - 1))]);
				rmin[i][j] = std::min(rmin[i - 1][j], rmin[i - 1][j + (1 << (i - 1))]);
			}
		}
	}
	
	int query_max(int l, int r) {
		int x = lg2[r - l + 1];
		return std::max(rmax[x][l], rmax[x][r - (1 << x) + 1]);
	}
	
	int query_min(int l, int r) {
		int x = lg2[r - l + 1];
		return std::min(rmin[x][l], rmin[x][r - (1 << x) + 1]);
	}
} st;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	n = read<int>(), q = read<int>();
	for (int i = 1; i <= n; i++)
		a[i] = read<int>();
	st.init();
	for (int i = 1; i <= q; i++) {
		int ql = read<int>(), qr = read<int>();
		write<int>(st.query_max(ql, qr) - st.query_min(ql, qr));
		puts("");
	}
	return 0;
}
