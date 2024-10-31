#include <bits/stdc++.h>

#define int __int128

constexpr int N = 1e5 + 7;

int n, P, q;
int a[N];

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

namespace SegTree {

	struct node {
		int val, lzy_add, lzy_mul;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void maketag(int o, int l, int r, int v, int t) {
		if (t == 1) {
			(tr[o].lzy_add *= v) %= P;
			(tr[o].lzy_mul *= v) %= P;
			(tr[o].val *= v) %= P;
		} else {
			(tr[o].lzy_add += v) %= P;
			(tr[o].val += (r - l + 1) * v) %= P;
		}
	}

	void pushup(const int o) {
		tr[o].val = (tr[ls(o)].val + tr[rs(o)].val) % P;
	}

	void pushdown(int o, int l, int r) {
		int mid = (l + r) >> 1;
		maketag(ls(o), l, mid, tr[o].lzy_mul, 1);
		maketag(ls(o), l, mid, tr[o].lzy_add, 2);
		maketag(rs(o), mid + 1, r, tr[o].lzy_mul, 1);
		maketag(rs(o), mid + 1, r, tr[o].lzy_add, 2);
		tr[o].lzy_mul = 1;
		tr[o].lzy_add = 0;
	}

	void build(int o, int l, int r) {
		if (l == r) { tr[o].val = a[l]; return; }
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
		tr[o].lzy_mul = 1;
	}

	void update(int o, int l, int r, int ql, int qr, int v, int t) {
		if (t == 1) {
			if (ql <= l && r <= qr)
				maketag(o, l, r, v, 1);
			else if (!((l > qr) || (r < ql))) {
				int mid = (l + r) >> 1;
				pushdown(o, l, r);
				update(ls(o), l, mid, ql, qr, v, t);
				update(rs(o), mid + 1, r, ql, qr, v, t);
				pushup(o);
			}
		} else {
			if (ql <= l && r <= qr)
				maketag(o, l, r, v, 2);
			else if (!((l > qr) || (r < ql))) {
				int mid = (l + r) >> 1;
				pushdown(o, l, r);
				update(ls(o), l, mid, ql, qr, v, t);
				update(rs(o), mid + 1, r, ql, qr, v, t);
				pushup(o);
			}
		}
	}

	int query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr)
			return tr[o].val;
		else if (!((l > qr) || (r < ql))) {
			int mid = (l + r) >> 1;
			pushdown(o, l, r);
			return (query(ls(o), l, mid, ql, qr) + query(rs(o), mid + 1, r, ql, qr)) % P;
		}
		return 0;
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	n = read<int>(), P = read<int>();
	for (int i = 1; i <= n; i++)
		a[i] = read<int>();
	SegTree::build(1, 1, n);
	q = read<int>();
	while (q--) {
		int opt = read<int>();
		if (opt == 1) {
			int x = read<int>(), y = read<int>(), k = read<int>();
			SegTree::update(1, 1, n, x, y, k, 1);
		} else if (opt == 2) {
			int x = read<int>(), y = read<int>(), k = read<int>();
			SegTree::update(1, 1, n, x, y, k, 2);
		} else {
			int x = read<int>(), y = read<int>();
			write<int>(SegTree::query(1, 1, n, x, y));
			puts("");
		}
	}
	return 0;
}
