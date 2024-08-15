#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 8e5 + 7;
constexpr i64 inf = std::numeric_limits<i64>::max();

int n, m;
int a[N], b[N], rk[N];

bool cmp(int i, int j) { return (a[i] == a[j]) ? i > j : a[i] > a[j]; }

int st[N][25], lg[N], pw[25];

struct ques {
	int l, r, id;
} q1[N], q2[N];

std::vector<ques> q[N];

void init() {
	for (int i = 0; i <= 21; i++)
		pw[i] = 1 << i;
	for (int i = 1; i <= n; i++) {
		lg[i] = lg[i - 1] + 1;
		while (pw[lg[i]] > i)
			--lg[i];
	}
}

int rt, lc[N], rc[N];

struct node {
	int tp;
	i64 val, var, k, b;
};

int rmq(int l, int r) {
	int tt = lg[r - l + 1];
	int tx = st[l][tt];
	int ty = st[r - pw[tt] + 1][tt];
	return rk[tx] < rk[ty] ? tx : ty;
}

i64 ans1[N], ans2[N], ans[N];

struct SegTree {
	node tr[N << 2];

	void build(int o, int l, int r) {
		tr[o].tp = tr[o].k = tr[o].b = 0;
		tr[o].val = tr[o].var = inf;
		if (l < r) {
			int mid = (l + r) >> 1;
			build(o << 1, l, mid);
			build(o << 1 | 1, mid + 1, r);
		}
	}

	void setit(int o, int l, int r, i64 k, i64 b) {
		tr[o].tp = 1;
		tr[o].k = k;
		tr[o].b = b;
		tr[o].val = l * k + b;
		tr[o].var = r * k + b;
	}

	void addit(int o, int l, int r, i64 k, i64 b) {
		tr[o].tp = tr[o].tp ? tr[o].tp : 2;
		tr[o].k += k;
		tr[o].b += b;
		tr[o].val += l * k + b;
		tr[o].var += r * k + b;
	}

	void downit(int o, int l, int r) {
		if (tr[o].tp) {
			int mid = (l + r) >> 1;
			if (tr[o].tp == 1) {
				setit(o << 1, l, mid, tr[o].k, tr[o].b);
				setit(o << 1 | 1, mid + 1, r, tr[o].k, tr[o].b);
			} else {
				addit(o << 1, l, mid, tr[o].k, tr[o].b);
				addit(o << 1 | 1, mid + 1, r, tr[o].k, tr[o].b);
			}
			tr[o].tp = tr[o].k = tr[o].b = 0;
		}
	}

	int ll, rr;
	i64 kk, bb;

	void set(int o, int l, int r) {
		if (ll <= l && r <= rr)
			setit(o, l, r, kk, bb);
		else {
			downit(o, l, r);
			int mid = (l + r) >> 1;
			if (ll <= mid) {
				set(o << 1, l, mid);
			}
			if (rr > mid) {
				set(o << 1 | 1, mid + 1, r);
			}
			tr[o].val = tr[o << 1].val;
			tr[o].var = tr[o << 1 | 1].var;
		}
	}

	void add(int o, int l, int r) {
		if (ll <= l && r <= rr)
			addit(o, l, r, kk, bb);
		else {
			downit(o, l, r);
			int mid = (l + r) >> 1;
			if (ll <= mid)
				set(o << 1, l, mid);
			if (rr > mid)
				set(o << 1 | 1, mid + 1, r);
			tr[o].val = tr[o << 1].val;
			tr[o].var = tr[o << 1 | 1].var;
		}
	}

	i64 query(int o, int l, int r, int p) {
		if (l == r)
			return tr[o].val;
		downit(o, l, r);
		int mid = (l + r) >> 1;
		return p <= mid ? query(o << 1, l, mid, p) : query(o << 1 | 1, mid + 1, r, p);
	}

	int _ll, _rr;
	i64 k1, b1, b2;

	void maintain(int o, int l, int r) {
		if (_ll <= l && r <= _rr) {
			if (l * k1 + b1 >= tr[o].val + b2) {
				addit(o, l, r, 0, b2);
				return;
			}
			if (r * k1 + b1 <= tr[o].var + b2) {
				setit(o, l, r, k1, b1);
				return;
			}
		}
		downit(o, l, r);
		int mid = (l + r) >> 1;
		if (_ll <= mid)
			maintain(o << 1, l, mid);
		if (_rr > mid)
			maintain(o << 1 | 1, mid + 1, r);
		tr[o].val = tr[o << 1].val;
		tr[o].var = tr[o << 1 | 1].var;
	}

	int _tl[N], _tr[N];

	void dfs1(int &o, int l, int r) {
		if (l > r) { o = 0; return; }
		o = rmq(l, r);
		_tl[o] = l, _tr[o] = r;
		dfs1(lc[o], l, o - 1);
		dfs1(rc[o], o + 1, r);
	}

	void dfs2(int x, bool s) {
		i64 u = a[x];
		if (lc[x]) {
			dfs2(lc[x], 0);
			u += query(1, 1, n, x - 1);
		}
		if (rc[x]) {
			dfs2(rc[x], 1);
		}
		ll = rr = x, kk = 0, bb = u;
		set(1, 1, n);
		if (x < _tr[x]) {
			_ll = x + 1;
			_rr = _tr[x];
			k1 = a[x];
			b1 = u - 1ll * x * a[x];
			b2 = a[x] * (x - _tl[x] + 1ll);
			maintain(1, 1, n);
		}
		if (s) {
			for (size_t i = 0; i < q[_tl[x]].size(); i++)
				ans[q[_tl[x]][i].id] = query(1, 1, n, q[_tl[x]][i].r);
		}
	}
} seg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	init();

	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		b[i] = i;
	}

	std::sort(b + 1, b + n + 1, cmp);
	for (int i = 1; i <= n; i++) {
		rk[b[i]] = i;
		st[i][0] = i;
	}
	for (int j = 1; j <= lg[n] + 1; j++) {
		for (int i = 1; i <= n; i++) {
			if (i + pw[j - 1] <= n) {
				int x = st[i][j - 1], y = st[i + pw[j - 1]][j - 1];
				st[i][j] = rk[x] < rk[y] ? x : y;
			}
		}
	}
	for (int i = 1, l, r; i <= m; i++) {
		std::cin >> l >> r;
		l++, r++;
		int mid = rmq(l, r);
		q1[i].id = i, q1[i].l = l, q1[i].r = mid - 1;
		q2[i].id = i, q2[i].l = mid + 1, q2[i].r = r;
		ans1[i] = 1ll * a[mid] * (r - mid + 1);
		ans2[i] = 1ll * a[mid] * (mid - l + 1);
	}

	for (int i = 1; i <= m; i++) {
		if (q2[i].l <= q2[i].r)
			q[q2[i].l].push_back(q2[i]);
	}
	seg.build(1, 1, n);
	seg.dfs1(rt, 1, n);
	seg.dfs2(rt, 1);
	for (int i = 1; i <= m; i++) {
		ans2[i] += ans[i];
	}
	std::reverse(a + 1, a + n + 1);
	std::reverse(rk + 1, rk + n + 1);
	for (int i = 0; i <= n; i++)
		st[i][0] = i;
	for (int j = 1; j <= lg[n] + 1; j++) {
		for (int i = 1; i <= n; i++) {
			if (i + pw[j - 1] <= n) {
				int x = st[i][j - 1];
				int y = st[i + pw[j - 1]][j - 1];
				st[i][j] = rk[x] < rk[y] ? x : y;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		q[i].clear();
	}
	for (int i = 1; i <= m; i++) {
		if (q1[i].l <= q1[i].r) {
			std::swap(q1[i].l, q1[i].r);
			q1[i].l = n - q1[i].l + 1;
			q1[i].r = n - q1[i].r + 1;	
			q[q1[i].l].push_back(q1[i]);
		}
	}
	seg.build(1, 1, n);
	seg.dfs1(rt, 1, n);
	seg.dfs2(rt, 1);
	for (int i = 1; i <= m; i++)
		ans1[i] += ans[i];
	for (int i = 1; i <= m; i++) {
		std::cout << std::min(ans1[i], ans2[i]) << "\n";
	}
	return 0;
}
