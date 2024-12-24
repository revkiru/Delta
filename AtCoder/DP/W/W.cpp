#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, m;

struct node {
	int l, r, w;

	friend bool operator < (const node &x, const node &y) {
		return x.r < y.r;
	}
} a[N];

std::vector<node> v[N];

struct SegTree {
	struct node {
		int mx, tag;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void build(int o, int l, int r) {
		tr[o].mx = 0, tr[o].tag = 0;
		if (l == r)
			return;
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
	}

	void pushup(const int o) {
		tr[o].mx = std::max(tr[ls(o)].mx, tr[rs(o)].mx);
	}

	void pushdown(const int o) {
		if (tr[o].tag) {
			tr[ls(o)].tag += tr[o].tag, tr[rs(o)].tag += tr[o].tag;
			tr[ls(o)].mx += tr[o].tag, tr[rs(o)].mx += tr[o].tag;
			tr[o].tag = 0;
		}
	}

	void update(int o, int l, int r, int ql, int qr, int x) {
		if (ql <= l && r <= qr) {
			tr[o].mx += x;
			tr[o].tag += x;
			return;
		}
		pushdown(o);
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update(ls(o), l, mid, ql, qr, x);
		if (qr > mid)
			update(rs(o), mid + 1, r, ql, qr, x);
		pushup(o);
	}
} seg;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, l, r, w; i <= m; i++) {
		std::cin >> l >> r >> w;
		a[i] = {l, r, w};
		v[r].push_back(a[i]);
	}

	seg.build(1, 1, n);
	for (int r = 1; r <= n; r++) {
		seg.update(1, 1, n, r, r, std::max(0ll, seg.tr[1].mx));
		for (int j = 0; j < v[r].size(); j++) {
			int l = v[r][j].l, w = v[r][j].w;
			seg.update(1, 1, n, l, r, w);
		}
	}

	std::cout << std::max(0ll, seg.tr[1].mx) << "\n";
	return 0;
}
