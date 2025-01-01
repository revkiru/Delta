#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, len;
int a[N], lsh[N << 1], rt[N << 1];
int ch[2][20], cnt[2];

struct ques {
	bool ty;
	int l, r, k;
	int pos, t;
} q[N];

struct PersistentSegTree {
	int rcnt;
	struct node {
		int ls, rs, val;
	} tr[N << 8];

	#define ls(o) (tr[o].ls)
	#define rs(o) (tr[o].rs)

	void update(int &o, int l, int r, int p, int v) {
		if (!o) { o = ++rcnt; }
		tr[o].val += v;
		if (l == r) { return; }
		int mid = (l + r) >> 1;
		if (p <= mid)
			update(ls(o), l, mid, p, v);
		else
			update(rs(o), mid + 1, r, p, v);
	}

	int query(int l, int r, int k) {
		if (l == r) { return l; }
		int siz = 0;
		int mid = (l + r) >> 1;
		for (int i = 1; i <= cnt[1]; i++)
			siz += tr[ls(ch[1][i])].val;
		for (int i = 1; i <= cnt[0]; i++)
			siz -= tr[ls(ch[0][i])].val;
		if (k <= siz) {
			for (int i = 1; i <= cnt[1]; i++)
				ch[1][i] = ls(ch[1][i]);
			for (int i = 1; i <= cnt[0]; i++)
				ch[0][i] = ls(ch[0][i]);
			return query(l, mid, k);
		} else {
			for (int i = 1; i <= cnt[1]; i++)
				ch[1][i] = rs(ch[1][i]);
			for (int i = 1; i <= cnt[0]; i++)
				ch[0][i] = rs(ch[0][i]);
			return query(mid + 1, r, k - siz);
		}
	}

	#define lowbit(x) (x & -x)

	void rangeUpdate(int x, int v) {
		int k = std::lower_bound(lsh + 1, lsh + len + 1, a[x]) - lsh;
		for (int i = x; i <= n; i += lowbit(i))
			update(rt[i], 1, len, k, v);
	}

	int rangeQuery(int l, int r, int k) {
		memset(ch, 0, sizeof(ch));
		cnt[0] = cnt[1] = 0;
		for (int i = r; i; i -= lowbit(i))
			ch[1][++cnt[1]] = rt[i];
		for (int i = l - 1; i; i -= lowbit(i))
			ch[0][++cnt[0]] = rt[i];
		return query(1, len, k);
	}
} pSeg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		lsh[++len] = a[i];
	}
	for (int i = 1; i <= m; i++) {
		char opt;
		std::cin >> opt;
		q[i].ty = (opt == 'Q');
		if (q[i].ty)
			std::cin >> q[i].l >> q[i].r >> q[i].k;
		else {
			std::cin >> q[i].pos >> q[i].t;
			lsh[++len] = q[i].t;
		}
	}

	std::sort(lsh + 1, lsh + len + 1);
	len = std::unique(lsh + 1, lsh + len + 1) - lsh - 1;
	for (int i = 1; i <= n; i++)
		pSeg.rangeUpdate(i, 1);
	for (int i = 1; i <= m; i++) {
		if (q[i].ty)
			std::cout << lsh[pSeg.rangeQuery(q[i].l, q[i].r, q[i].k)] << "\n";
		else {
			pSeg.rangeUpdate(q[i].pos, -1);
			a[q[i].pos] = q[i].t;
			pSeg.rangeUpdate(q[i].pos, 1);
		}
	}

	return 0;
}
