#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr i64 inf = std::numeric_limits<i64>::max();

int n, q;
int a[N];

struct node {
	i64 l, r, len, mx, mn, sum, lzy;
};

struct SegTree {
	node tr[N << 8];

	i64 div(i64 x, i64 y) {
		if (x >= 0) return x / y;
		return -((y - x - 1) / y);
	}

	void add(int o, i64 k) {
		tr[o].lzy += k;
		tr[o].sum += k * tr[o].len;
		tr[o].mn += k, tr[o].mx += k;
	}

	void pushup(int o) {
		tr[o].mn = std::min(tr[o << 1].mn, tr[o << 1 | 1].mn);
		tr[o].mx = std::max(tr[o << 1].mx, tr[o << 1 | 1].mx);
		tr[o].sum = tr[o << 1].sum + tr[o << 1 | 1].sum;
	}

	void pushdown(int o) {
		if (tr[o].lzy != 0) {
			i64 k = tr[o].lzy;
			int l = o << 1, r = o << 1 | 1;
			add(l, k);
			add(r, k);
			tr[o].lzy = 0;
		}
	}

	void build(int o, int l, int r) {
		tr[o].l = l, tr[o].r = r, tr[o].len = r - l + 1;
		if (l == r) {	
			tr[o].mx = tr[o].mn = tr[o].sum = a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(o << 1, l, mid);
		build(o << 1 | 1, mid + 1, r);
		pushup(o);
	}

	void rangeAdd(int o, int l, int r, i64 k) {
		if (tr[o].r < l || tr[o].l > r) return;
		if (l <= tr[o].l && tr[o].r <= r) {
			add(o, k);
			return;
		}
		pushdown(o);
		rangeAdd(o << 1, l, r, k);
		rangeAdd(o << 1 | 1, l, r, k);
		pushup(o);
	}

	void rangeDiv(int o, int l, int r, i64 k) {
		if (tr[o].r < l || tr[o].l > r) return;
		if (l <= tr[o].l && tr[o].r <= r && tr[o].l == tr[o].r) {
			tr[o].mn = tr[o].mx = tr[o].sum = div(tr[o].sum, k);
			return;
		}
		pushdown(o);
		if (l <= tr[o].l && tr[o].r <= r && (tr[o].mn - div(tr[o].mn, k) == tr[o].mx - div(tr[o].mx, k))) {
			add(o, div(tr[o].mx, k) - tr[o].mx);
			return;
		}
		rangeDiv(o << 1, l, r, k);
		rangeDiv(o << 1 | 1, l, r, k);
		pushup(o);
	}

	i64 queryMn(int o, int l, int r) {
		if (tr[o].r < l || tr[o].l > r) return inf;
		if (l <= tr[o].l && tr[o].r <= r) return tr[o].mn;
		pushdown(o);
		return std::min(queryMn(o << 1, l, r), queryMn(o << 1 | 1, l, r));
	}

	i64 querySum(int o, int l, int r) {
		if (tr[o].r < l || tr[o].l > r) return 0;
		if(l <= tr[o].l && tr[o].r <= r) return tr[o].sum;
		pushdown(o);
		return (querySum(o << 1, l, r) + querySum(o << 1 | 1, l, r));
	}
} seg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	seg.build(1, 1, n);
	while (q--) {
		int opt, l, r;
		i64 x;
		std::cin >> opt;
		if (opt == 1) {	
			std::cin >> l >> r >> x;
			l++, r++;
			seg.rangeAdd(1, l, r, x);
		} else if (opt == 2) {
			std::cin >> l >> r >> x;
			l++, r++;
			seg.rangeDiv(1, l, r, x);
		} else if (opt == 3) {
			std::cin >> l >> r;
			l++, r++;
			std::cout << seg.queryMn(1, l, r) << "\n";
		} else if (opt == 4) {
			std::cin >> l >> r;
			l++, r++;
			std::cout << seg.querySum(1, l, r) << "\n";
		}
	}
	return 0;
}
