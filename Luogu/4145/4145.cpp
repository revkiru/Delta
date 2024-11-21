#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;
i64 a[N];

struct node {
	i64 mx, sum;
};

struct SegTree {
	node tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void pushup(const int o) {
		tr[o].mx = std::max(tr[ls(o)].mx, tr[rs(o)].mx);
		tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum;
	}

	void build(int o, int l, int r) {
		if (l == r) {
			tr[o].sum = tr[o].mx = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
	}

	void update(int o, int l, int r, int ql, int qr) {
		if (l == r && (ql <= l && r <= qr)) {
			tr[o].sum = tr[o].mx = std::sqrt(tr[o].sum);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid && tr[ls(o)].mx > 1)
			update(ls(o), l, mid, ql, qr);
		if (qr > mid && tr[rs(o)].mx > 1)
			update(rs(o), mid + 1, r, ql, qr);
		pushup(o);
	}

	i64 query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr)
			return tr[o].sum;
		int mid = (l + r) >> 1;
		i64 ret = 0;
		if (ql <= mid)
			ret += query(ls(o), l, mid, ql, qr);
		if (qr > mid)
			ret += query(rs(o), mid + 1, r, ql, qr);
		return ret;
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
	while (m--) {
		int opt, l, r;
		std::cin >> opt >> l >> r;
		if (l > r)
			std::swap(l, r);
		if (opt == 0) {
			seg.update(1, 1, n, l, r);
		} else {
			std::cout << seg.query(1, 1, n, l, r) << "\n";
		}
	}
	return 0;
}
