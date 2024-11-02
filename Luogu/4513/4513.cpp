#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, m;
int a[N];

struct SegTree {
	struct node {
		int val, sum, lmax, rmax;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void pushup(const int o) {
		tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum;
		tr[o].val = std::max({tr[ls(o)].val, tr[ls(o)].rmax + tr[rs(o)].lmax, tr[rs(o)].val});
		tr[o].lmax = std::max(tr[ls(o)].lmax, tr[ls(o)].sum + tr[rs(o)].lmax);
		tr[o].rmax = std::max(tr[rs(o)].rmax, tr[rs(o)].sum + tr[ls(o)].rmax);
	}

	void build(int o, int l, int r) {
		if (l == r) {
			tr[o].val = tr[o].sum = tr[o].lmax = tr[o].rmax = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
	}

	void update(int o, int l, int r, int x, int v) {
		if (l == r) {
			// std::cout << l << "---" << v << "---\n";
			tr[o].val = tr[o].sum = tr[o].lmax = tr[o].rmax = v;
			return;
		}
		int mid = (l + r) >> 1;
		if (x <= mid)
			update(ls(o), l, mid, x, v);
		else
			update(rs(o), mid + 1, r, x, v);
		pushup(o);
	}

	node query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr)
			return tr[o];
		int mid = (l + r) >> 1;
		if (qr <= mid)
			return query(ls(o), l, mid, ql, qr);
		if (ql > mid)
			return query(rs(o), mid + 1, r, ql, qr);
		node ret;
		node ch0 = query(ls(o), l, mid, ql, qr);
		node ch1 = query(rs(o), mid + 1, r, ql, qr);
		ret.sum = ch0.sum + ch1.sum;
		ret.val = std::max({ch0.val, ch1.val, ch0.rmax + ch1.lmax});
		ret.lmax = std::max(ch0.lmax, ch0.sum + ch1.lmax);
		ret.rmax = std::max(ch1.rmax, ch1.sum + ch0.rmax);
		return ret;
	}
} seg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	seg.build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int opt, x, y;
		std::cin >> opt >> x >> y;
		if (opt == 1) {
			if (x > y)
				std::swap(x, y);
			std::cout << seg.query(1, 1, n, x, y).val << "\n";
		} else {
			// std::cout << y << "!\n";
			seg.update(1, 1, n, x, y);
		}
	}
	return 0;
}
