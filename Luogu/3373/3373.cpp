#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, q;
int a[N];

namespace SegTree {
	#define P m

	struct node {
		i64 val, lzy_add, lzy_mul;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void maketag(int o, int l, int r, i64 v, int t) {
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

	void update(int o, int l, int r, int ql, int qr, i64 v, int t) {
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

	i64 query(int o, int l, int r, int ql, int qr) {
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

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	SegTree::build(1, 1, n);
	while (q--) {
		int opt, x, y, k;
		std::cin >> opt;
		if (opt == 1) {
			std::cin >> x >> y >> k;
			SegTree::update(1, 1, n, x, y, k, 1);
		} else if (opt == 2) {
			std::cin >> x >> y >> k;
			SegTree::update(1, 1, n, x, y, k, 2);
		} else {
			std::cin >> x >> y;
			std::cout << SegTree::query(1, 1, n, x, y) << "\n";
		}
	}
	return 0;
}
