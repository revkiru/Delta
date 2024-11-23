#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;
constexpr int B = 10000;
constexpr int M = 65;

int n, m, p, c, t0t;
int a[N], phi[N], exm[B + 7][M][2];
bool flg, ovr[B + 7][M][2];

int genPhi(int x) {
	int ret = x;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0)
			ret = ret / i * (i - 1);
		while (x % i == 0)
			x /= i;
	}
	if (x > 1)
		ret = ret / x * (x - 1);
	return ret;
}

void init() {
	int x = p;
	phi[0] = x;
	while (x > 1) { x = genPhi(x); phi[++t0t] = x; }
	phi[++t0t] = 1;

	for (int i = 0; i <= t0t; i++) {
		exm[0][i][0] = 1;
		for (int j = 1; j <= B; j++) {
			exm[j][i][0] = exm[j - 1][i][0] * c;
			if (exm[j][i][0] >= phi[i]) {
				ovr[j][i][0] = 1;
				exm[j][i][0] %= phi[i];
			}
			ovr[j][i][0] |= ovr[j - 1][i][0];
		}
	}
	for (int i = 0; i <= t0t; i++) {
		exm[0][i][1] = 1;
		for (int j = 1; j <= B; j++) {
			exm[j][i][1] = exm[j - 1][i][1] * exm[B][i][0];
			if (exm[j][i][1] >= phi[i]) {
				ovr[j][i][1] = 1;
				exm[j][i][1] %= phi[i];
			}
			ovr[j][i][1] |= ovr[j - 1][i][1];
		}
	}
}

int lightPow(int d, int p) {
	flg |= ovr[d % B][p][0] | ovr[d / B][p][1];
	int ret = exm[d % B][p][0] * exm[d / B][p][1];
	if (ret >= phi[p]) {
		flg = 1;
		ret %= phi[p];
	}
	return ret;
}

int calc(int idx, int lim, int d) {
	flg = 0;
	if (d == lim) {
		if (a[idx] >= phi[d]) {
			flg = 1;
			return a[idx] % phi[d];
		}
		return a[idx];
	}
	int x = calc(idx, lim, d + 1);
	if (flg) { x += phi[d + 1]; flg = 0; }
	return lightPow(x, d);
}

struct node {
	int sum, tim;
};

struct SegTree {
	node tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void pushup(const int o) {
		tr[o].sum = (tr[ls(o)].sum + tr[rs(o)].sum) % p;
		tr[o].tim = std::min(tr[ls(o)].tim, tr[rs(o)].tim);
	}

	void build(int o, int l, int r) {
		if (l == r) {
			tr[o].sum = a[l];
			tr[o].tim = 0;
			return;
		}
		int mid = (l + r) >> 1;
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		pushup(o);
	}

	void update(int o, int l, int r, int ql, int qr) {
		if (tr[o].tim >= t0t)
			return;
		if (l == r) {
			tr[o].tim++;
			tr[o].sum = calc(l, tr[o].tim, 0);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update(ls(o), l, mid, ql, qr);
		if (qr > mid)
			update(rs(o), mid + 1, r, ql, qr);
		pushup(o);
	}

	int query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			return tr[o].sum;
		}
		int mid = (l + r) >> 1;
		int ret = 0;
		if (ql <= mid)
			ret += query(ls(o), l, mid, ql, qr);
		if (qr > mid)
			ret += query(rs(o), mid + 1, r, ql, qr);
		return ret % p;
	}
} seg;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m >> p >> c;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	init();
	seg.build(1, 1, n);
	while (m--) {
		int opt, x, y;
		std::cin >> opt >> x >> y;
		if (opt == 0) {
			seg.update(1, 1, n, x, y);
		} else {
			std::cout << seg.query(1, 1, n, x, y) << "\n";
		}
	}
	return 0;
}
