#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

int n, m, d;
int ans;
int idx[N];

struct node {
	int x, h;
} p[N];

bool cmp(const node &x, const node &y) {
	return x.x < y.x;
}

struct SegTree {
	struct node {
		int val, tag;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void pushup(const int o) {
		tr[o].val = tr[ls(o)].val + tr[rs(o)].val;
	}

	void pushdown(int o, int l, int r) {
		if (tr[o].tag) {
			tr[ls(o)].tag += tr[o].tag;
			tr[rs(o)].tag += tr[o].tag;

			int mid = (l + r) >> 1;
			tr[ls(o)].val += (mid - l + 1) * tr[o].tag;
			tr[rs(o)].val += (r - mid) * tr[o].tag;
		}
		tr[o].tag = 0;
	}

	void build(int o, int l, int r) {
		tr[o].val = 0;
		if (l == r) {
			tr[o].val = p[l].h;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
	}

	void update(int o, int l, int r, int ql, int qr, int v) {
		if (ql <= l && r <= qr) {
			tr[o].tag += v;
			tr[o].val += v * (r - l + 1);
			return;
		}
		pushdown(o, l, r);
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update(ls(o), l, mid, ql, qr, v);
		if (qr > mid)
			update(rs(o), mid + 1, r, ql, qr, v);
		pushup(o);
	}

	int query(int o, int l, int r, int x) {
		if (l == r)
			return tr[o].val;
		pushdown(o, l, r);
		int mid = (l + r) >> 1;
		if (x <= mid)
			return query(ls(o), l, mid, x);
		else
			return query(rs(o), mid + 1, r, x);
	}
} seg;

int myceil(int a, int b) {
	if (!(a % b)) return a / b;
	return a / b + 1;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> d >> m;
	for (int i = 1; i <= n; i++)
		std::cin >> p[i].x >> p[i].h;
	std::sort(p + 1, p + n + 1, cmp);
	for (int i = 1; i <= n; i++)
		idx[i] = p[i].x;

	seg.build(1, 1, n);
	for (int i = 1; i <= n; i++) {
		int lim = p[i].x + d * 2;
		int val = seg.query(1, 1, n, i);
		if (val <= 0) continue;
		int tar = std::upper_bound(idx + 1, idx + n + 1, lim) - idx;
		int cnt = myceil(val, m);
		ans += cnt, tar--;
		seg.update(1, 1, n, i, tar, -cnt * m);
	}
	std::cout << ans << "\n";
	return 0;
}
