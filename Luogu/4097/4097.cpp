#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int P1 = 39989;
constexpr int P2 = 1e9;
constexpr double eps = 1e-9;

int n, lstAns;

struct line {
	double k, b;
} p[N];

int cmp(double x, double y) {
	if (x - y > eps) return 1;
	if (y - x > eps) return -1;
	return 0;
}

struct LiChaoTree {
	int t0t, tr[N << 1];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	double calc(int idx, int x) { return x * p[idx].k + p[idx].b; }

	void add(int x0, int y0, int x1, int y1) {
		t0t++;
		if (x0 == x1) {	// 无斜率
			p[t0t].k = 0;
			p[t0t].b = std::max(y0, y1);
		} else {
			p[t0t].k = 1.0 * (y1 - y0) / (x1 - x0);
			p[t0t].b = y0 - p[t0t].k * x0;
		}
	}

	void modify(int o, int l, int r, int u) {	// 完全覆盖
		int &v = tr[o], mid = (l + r) >> 1;
		int bmid = cmp(calc(u, mid), calc(v, mid));
		if (bmid == 1 || (!bmid && u < v))
			std::swap(u, v);
		int bl = cmp(calc(u, l), calc(v, l)), br = cmp(calc(u, r), calc(v, r));
		if (bl == 1 || (!bl && u < v))
			modify(ls(o), l, mid, u);
		if (br == 1 || (!br && u < v))
			modify(rs(o), mid + 1, r, u);
	}

	void update(int o, int l, int r, int ql, int qr, int u) {	// 寻找定位线段继续覆盖的区间
		if (ql <= l && r <= qr) {
			modify(o, l, r, u);
			return;
		}
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update(ls(o), l, mid, ql, qr, u);
		if (qr > mid)
			update(rs(o), mid + 1, r, ql, qr, u);
	}

	std::pair<double, int> lmax(std::pair<double, int> x, std::pair<double, int> y) {
		if (cmp(x.first, y.first) == -1)
			return y;
		if (cmp(x.first, y.first) == 1)
			return x;
		return x.second < y.second ? x : y;
	}

	std::pair<double, int> query(int o, int l, int r, int p) {
		if (r < p || p < l)
			return {0, 0};
		int mid = (l + r) >> 1;
		double ret = calc(tr[o], p);
		if (l == r)
			return {ret, tr[o]};
		return lmax({ret, tr[o]}, lmax(query(ls(o), l, mid, p), query(rs(o), mid + 1, r, p)));
	}
} lcTr;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("4097.in", "r", stdin);
	// freopen("4097.out", "w", stdout);

	std::cin >> n;
	while (n--) {
		int opt, x, x0, y0, x1, y1;
		std::cin >> opt;
		if (opt == 1) {
			std::cin >> x0 >> y0 >> x1 >> y1;
			x0 = (x0 + lstAns - 1 + P1) % P1 + 1;
			x1 = (x1 + lstAns - 1 + P1) % P1 + 1;
			y0 = (y0 + lstAns - 1 + P2) % P2 + 1;
			y1 = (y1 + lstAns - 1 + P2) % P2 + 1;
			if (x0 > x1) {
				std::swap(x0, x1);
				std::swap(y0, y1);
			}
			lcTr.add(x0, y0, x1, y1);
			lcTr.update(1, 1, P1, x0, x1, lcTr.t0t);
		} else {
			std::cin >> x;
			x = (x + lstAns - 1 + P1) % P1 + 1;
			std::cout << (lstAns = lcTr.query(1, 1, P1, x).second) << "\n";
		}
	}
	return 0;
}
