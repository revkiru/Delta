#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;
constexpr int P = 998244353;
constexpr int I = (P + 1) / 2;

int n, m, tot;
int num[N], pw2[N], inv[N], f[2][N], sum[2][N];

struct node {
	int l, r, c;
} a[N];

struct SegTree {
	struct node {
		int sum, tag;
	} tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void build(int o, int l, int r) {
		tr[o] = {0, 1};
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
	}

	void pushdown(const int o) {
		tr[ls(o)].sum = tr[ls(o)].sum * tr[o].tag % P;
		tr[rs(o)].sum = tr[rs(o)].sum * tr[o].tag % P;
		tr[ls(o)].tag = tr[ls(o)].tag * tr[o].tag % P;
		tr[rs(o)].tag = tr[rs(o)].tag * tr[o].tag % P;
		tr[o].tag = 1;
	}

	void update1(int o, int l, int r, int p, int v) {
		if (l == r) { tr[o].sum = v; return; }
		if (tr[o].tag != 1) pushdown(o);
		int mid = (l + r) >> 1;
		if (p <= mid) update1(ls(o), l, mid, p, v);
		else update1(rs(o), mid + 1, r, p, v);
		tr[o].sum = (tr[ls(o)].sum + tr[rs(o)].sum) % P;
	}

	void update2(int o, int l, int r, int ql, int qr) {
		if (ql > qr) return;
		if (ql <= l && r <= qr) {
			tr[o] = {tr[o].sum * 2 % P, tr[o].tag * 2 % P};
			return;
		}
		if (tr[o].tag != 1) pushdown(o);
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update2(ls(o), l, mid, ql, qr);
		if (qr > mid)
			update2(rs(o), mid + 1, r, ql, qr);
		tr[o].sum = (tr[ls(o)].sum + tr[rs(o)].sum) % P;
	}

	int query(int o, int l, int r, int ql, int qr) {
		if (ql > qr) return 0;
		if (ql <= l && r <= qr) return tr[o].sum;
		if (tr[o].tag != 1) pushdown(o);
		int mid = (l + r) >> 1, res = 0;
		if (ql <= mid) { res += query(ls(o), l, mid, ql, qr); res %= P; }
		if (qr > mid) { res += query(rs(o), mid + 1, r, ql, qr); res %= P; }
		return res;
	}
} seg[2];

void init() {
	const int R = 1e5;
	pw2[0] = inv[0] = 1;
	for (int i = 1; i <= R; i++) {
		pw2[i] = (pw2[i - 1] * 2) % P;
		inv[i] = (inv[i - 1] * I) % P;
	}
}

void solve() {
	std::cin >> n;
	tot = 0;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i].l >> a[i].r >> a[i].c;
		num[++tot] = a[i].l;
		num[++tot] = a[i].r;
	}
	std::sort(num + 1, num + tot + 1);
	tot = std::unique(num + 1, num + tot + 1) - num - 1;
	for (int i = 1; i <= n; i++) {
		a[i].l = std::lower_bound(num + 1, num + tot + 1, a[i].l) - num;
		a[i].r = std::lower_bound(num + 1, num + tot + 1, a[i].r) - num;
	}
	std::sort(a + 1, a + n + 1, [&](const auto &x, const auto &y) { return x.r < y.r; });
	for (int i = 1; i <= tot; i++)
		sum[0][i] = sum[1][i] = 0;
	for (int i = 1; i <= n; i++)
		sum[a[i].c][a[i].r]++;
	for (int i = 1; i <= tot; i++) {
		sum[0][i] += sum[0][i - 1];
		sum[1][i] += sum[1][i - 1];
	}
	seg[0].build(1, 1, n);
	seg[1].build(1, 1, n);
	for (int i = 1; i <= n; i++)
		f[0][i] = f[1][i] = 0;
	int cnt[2] = {0, 0};
	for (int i = 1; i <= n; i++) {
		cnt[a[i].c]++;
		f[a[i].c][i] = (seg[!a[i].c].query(1, 1, n, 1, sum[!a[i].c][a[i].l - 1]) + pw2[cnt[a[i].c] - 1]) % P;
		seg[!a[i].c].update2(1, 1, n, 1, sum[!a[i].c][a[i].l - 1]);
		seg[a[i].c].update1(1, 1, n, cnt[a[i].c], f[a[i].c][i]);
	}
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		ans = (ans + f[0][i]) % P;
		ans = (ans + f[1][i]) % P;
	}
	std::cout << ans << "\n";
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	init();
	int t;
	std::cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}
