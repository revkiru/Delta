#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n, m, tot, las;
int a[N], pre[N], suf[N];

std::map<int, int> mp;
std::set<int> s[N << 2];

struct node {
	int lval, rval, mx, mn, mnp, gc;
};

struct SegTree {
	node tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	node pushup(node u, node v) {
		return {u.lval, v.rval, std::max(u.mx, v.mx), std::min(u.mn, v.mn), std::max(u.mnp, v.mnp), std::__gcd(std::__gcd(u.gc, v.gc), std::abs(u.lval - v.lval))};
	}
	
	void build(int o, int l, int r) {
		if (l == r) {
			tr[o] = {a[l], a[l], a[l], a[l], pre[l], 0};
			// std::cout << l << "!!!\n";
			return;
		}
		int mid = (l + r) >> 1;
		// std::cout << r << "---\n";
		build(ls(o), l, mid);
		build(rs(o), mid + 1, r);
		// std::cout << o << "---\n";
		tr[o] = pushup(tr[ls(o)], tr[rs(o)]);
	}
	
	void update(int o, int l, int r, int p, node v) {
		if (l > p || r < p)
			return;
		if (l == r) {
			tr[o] = v;
			return;
		}
		int mid = (l + r) >> 1;
		update(ls(o), l, mid, p, v);
		update(rs(o), mid + 1, r, p, v);
		tr[o] = pushup(tr[ls(o)], tr[rs(o)]);
	}
	
	node query(int o, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) {
			// std::cout << l << "!!!\n";
			return tr[o];
		}
		int mid = (l + r) >> 1;
		if (qr <= mid)
			return query(ls(o), l, mid, ql, qr);
		if (ql > mid)
			return query(rs(o), mid + 1, r, ql, qr);
		return pushup(query(ls(o), l, mid, ql, qr), query(rs(o), mid + 1, r, ql, qr));
	}
} seg;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("5278_ex/P5278_1.in", "r", stdin);
	// freopen("P5278.out", "w", stdout);

	std::cin >> n >> m;
	// std::cout << n << "---" << m << "\n";
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		a[i] = x;
		if (mp.find(x) == mp.end()) {
			mp[x] = ++tot;
			s[tot].insert(i);
		} else {
			int y = mp[x];
			int z = *(--s[y].end());
			pre[i] = z;
			suf[z] = i;
			s[y].insert(i);
		}
	}
	// std::cout << mp.size() << "\n";
	// for (int i = 1; i <= n; i++) {
	// 	std::cout << pre[i] << " " << suf[i] << "\n";
	// }
	seg.build(1, 1, n);
	for (int i = 1; i <= m; i++) {
		int opt, x, y, z;
		std::cin >> opt;
		if (opt == 1) {
			std::cin >> x >> y;
			x ^= las, y ^= las;
			suf[pre[x]] = suf[x];
			pre[suf[x]] = pre[x];
			z = a[suf[x]];
			seg.update(1, 1, n, suf[x], {z, z, z, z, pre[x], 0});
			s[mp[a[x]]].erase(x);
			if (mp.find(y) == mp.end()) {
				mp[y] = ++tot;
				s[tot].insert(x);
				pre[x] = suf[x] = 0;
			} else {
				z = mp[y];
				auto it = s[z].lower_bound(x);
				if (it == s[z].begin()) {
					pre[x] = 0;
					suf[x] = *it;
					pre[*it] = x;
					seg.update(1, 1, n, *it, {a[*it], a[*it], a[*it], a[*it], x, 0});
				} else if (it == s[z].end()) {
					it--;
					pre[x] = *it;
					suf[x] = 0;
					suf[*it] = x;
				} else {
					auto _it = --it;
					it++;
					pre[x] = *_it;
					suf[x] = *it;
					suf[*_it] = x;
					pre[*it] = x;
					seg.update(1, 1, n, *it, {a[*it], a[*it], a[*it], a[*it], x, 0});
				}
			}
			a[x] = y;
			seg.update(1, 1, n, x, {y, y, y, y, pre[x], 0});
		} else {
			std::cin >> x >> y >> z;
			x ^= las, y ^= las, z ^= las;
			node d = seg.query(1, 1, n, x, y);
			if ((d.mx - d.mn == 1ll * z * (y - x)) && (d.gc == z || !d.gc) && (d.mnp < x || !z)) {
				las++;
				std::cout << "Yes\n";
			} else {
				std::cout << "No\n";
			}
		}
	}
	return 0;
}
