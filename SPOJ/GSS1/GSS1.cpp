#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, m;
int a[N];

struct SegTree {
	struct node {
		int dat, sum, lmx, rmx;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void pushup(const int o) {
		tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum;
		tr[o].lmx = std::max(tr[ls(o)].lmx, tr[ls(o)].sum + tr[rs(o)].lmx);
		tr[o].rmx = std::max(tr[rs(o)].rmx, tr[rs(o)].sum + tr[ls(o)].rmx);
		tr[o].dat = std::max({tr[ls(o)].dat, tr[rs(o)].dat, tr[ls(o)].rmx + tr[rs(o)].lmx});
	}

	void build(int o, int l, int r) {
		if (l == r) {
			tr[o].sum = tr[o].lmx = tr[o].rmx = tr[o].dat = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
	}

	node query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr)
			return tr[o];
		int mid = (l + r) >> 1;
		if (ql > mid) return query(rs(o), mid + 1, r, ql, qr);
		if (qr <= mid) return query(ls(o), l, mid, ql, qr);
		else {
			node x, y;
			x = query(ls(o), l, mid, ql, qr);
			y = query(rs(o), mid + 1, r, ql, qr);
			return { std::max({x.dat, x.rmx + y.lmx, y.dat}), x.sum + y.sum, std::max(x.lmx, x.sum + y.lmx), std::max(y.rmx, y.sum + x.rmx) };
		}
	}
} seg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	seg.build(1, 1, n);
	std::cin >> m;
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		std::cout << seg.query(1, 1, n, x, y).dat << "\n";
	}
	return 0;
}
