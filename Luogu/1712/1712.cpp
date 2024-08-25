#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int inf = 0x3f3f3f3f;

int n, m, wR;
int L[N << 1], R[N << 1];

struct line {
	int len, id;
} a[N << 2];

int t0t;
struct node {
	int val, id;
} p[N << 2];

template <typename T>
struct chd {
	T val, lzy;
};

template <typename T>
struct SegTree {
	chd<T> tr[N << 3];

	void pushdown(T o) {
		if (!tr[o].lzy) return;
		tr[o << 1].val += tr[o].lzy;
		tr[o << 1].lzy += tr[o].lzy;
		tr[o << 1 | 1].val += tr[o].lzy;
		tr[o << 1 | 1].lzy += tr[o].lzy;
		tr[o].lzy = 0;
	}

	void update(T o, T l, T r, T ql, T qr, T val) {
		if (ql > r || qr < l) { return; }
		if (ql <= l && r <= qr) { tr[o].val += val; tr[o].lzy += val; return; }
		int mid = (l + r) >> 1;
		pushdown(o);
		update(o << 1, l, mid, ql, qr, val);
		update(o << 1 | 1, mid + 1, r, ql, qr, val);
		tr[o].val = std::max(tr[o << 1].val, tr[o << 1 | 1].val);
	}
};

SegTree<int> seg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		int l, r;
		std::cin >> l >> r;
		a[i].len = r - l;
		a[i].id = i;
		p[++t0t].val = l;
		p[t0t].id = i;
		p[++t0t].val = r;
		p[t0t].id = i;
	}

	std::sort(p + 1, p + t0t + 1, [](const node &x, const node &y) { return (x.val < y.val ? true : false); });
		// for  (int i = 1; i <= t0t; i++)
		// 	std::cout << p[i].val << " ";
		// std::cout << "\n";
	int ret = 0;
	p[0].val = -1;
	for (int i = 1; i <= t0t; i++) {
		if (p[i].val != p[i - 1].val)
			ret++;
		int u = p[i].id;
		if (!L[u]) L[u] = ret;
		else R[u] = ret;
	}
	// for (int i = 1; i <= t0t; i++) {
	// 	std::cout << "l, r: " << i << "\n";
    // 	std::cout << L[i] << " " << R[i] << "\n";
	// }

	wR = ret;
	std::sort(a + 1, a + n + 1, [](const line &x, const line &y) { return (x.len < y.len ? true : false); });
	// for  (int i = 1; i <= n; i++)
	// 	std::cout << a[i].len << " ";
	// std::cout << "\n";

	int ans = inf, lft = 0, rgt = 0;
	while (1) {
		while (seg.tr[1].val < m && rgt <= n) {
			rgt++;
			// std::cout << rgt << "h\n";
			int u = a[rgt].id;
			int v = L[u], w = R[u];
			seg.update(1, 1, wR, v, w, 1);
		}
		// std::cout << seg.tr[1].val << "--\n";
		if (seg.tr[1].val < m) break;
		while (seg.tr[1].val >= m && lft <= n) {
			lft++;
			int u = a[lft].id;
			int v = L[u], w = R[u];
			seg.update(1, 1, wR, v, w, -1);
		}
		ans = std::min(ans, a[rgt].len - a[lft].len);
	}

	std::cout << ((ans == inf) ? -1 : ans) << "\n";
	return 0;
}
