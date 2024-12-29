#include <bits/stdc++.h>

#define int long long

#define powit(x) (x * x)

constexpr int N = 2e5 + 7;
constexpr int M = 1e6;
constexpr int inf = 1e18;

int n, c, rt, lcnt;
int a[N], dp[N];

struct line {
	int k, b;
} s[N];

struct LiChaoTree {
	int rcnt;

	struct node {
		int l, r, id;
	} tr[M << 1];

	#define ls(o) (tr[o].l)
	#define rs(o) (tr[o].r)

	bool cmp(int x, int y, int k) {
		int f1 = s[x].k * k + s[x].b;
		int f2 = s[y].k * k + s[y].b;
		if (f1 == f2) return x < y;
		return f1 < f2;
	}

	void insert(int &o, int l, int r, int ql, int qr, int id) {
		if (!o) o = ++rcnt;
		int mid = (l + r) >> 1;
		if (ql <= l && r <= qr) {
			if (cmp(id, tr[o].id, l) && cmp(id, tr[o].id, r)) {
				tr[o].id = id;
				return;
			}
			if (cmp(tr[o].id, id, l) && cmp(tr[o].id, id, r))
				return;
			if (cmp(id, tr[o].id, mid))
				std::swap(id, tr[o].id);
			if (cmp(id, tr[o].id, l))
				insert(ls(o), l, mid, ql, qr, id);
			if (cmp(id, tr[o].id, r))
				insert(rs(o), mid + 1, r, ql, qr, id);
		} else {
			if (ql <= mid)
				insert(ls(o), l, mid, ql, qr, id);
			if (qr > mid)
				insert(rs(o), mid + 1, r, ql, qr, id);
		}
	}

	int query(int o, int l, int r, int x) {
		if (l == x && r == x)
			return tr[o].id;
		int mid = (l + r) >> 1, ret = 0;
		if (x <= mid)
			ret = query(ls(o), l, mid, x);
		else
			ret = query(rs(o), mid + 1, r, x);
		if (cmp(tr[o].id, ret, x))
			ret = tr[o].id;
		return ret;
	}
} lcst;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> c;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	s[0] = {0, inf};
	s[++lcnt] = {-2 * a[1], powit(a[1])};
	lcst.insert(rt, 1, M, 1, M, lcnt);
	for (int i = 2; i <= n; i++) {
		int x = lcst.query(rt, 1, M, a[i]);
		dp[i] = s[x].k * a[i] + s[x].b + powit(a[i]) + c;
		s[++lcnt] = {-2 * a[i], dp[i] + powit(a[i])};
		lcst.insert(rt, 1, M, 1, M, lcnt);
	}
	std::cout << dp[n] << "\n";
	return 0;
}
