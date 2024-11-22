#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 8e4 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, m;
int a[N], pos[N];

struct node {
	int rd, siz, val, ls, rs, fa;
};

struct FHQ_Treap {
	int tim, rt, l, r, mid, sum;
	node tr[N << 1];

	int newnode(int x) {
		tim++;
		tr[tim].val = x; tr[tim].siz = 1; tr[tim].rd = myrand();
		tr[tim].ls = tr[tim].rs = tr[tim].fa = 0;
		// std::cout << tim << "-" << tr[tim].val << "-" << tr[tim].siz << "-" << tr[tim].rd << "-" << tr[tim].ls << "-" << tr[tim].rs << "-" << tr[tim].fa << "\n";
		return tim;
	}

	void pushup(int o) {
		tr[o].siz = 1;
		if (tr[o].ls) {
			tr[o].siz += tr[tr[o].ls].siz;
			tr[tr[o].ls].fa = o;
		}
		if (tr[o].rs) {
			tr[o].siz += tr[tr[o].rs].siz;
			tr[tr[o].rs].fa = o;
		}
		// std::cout << o << "!!! " << tr[o].siz << "!!!\n";
	}

	void split(int o, int k, int &x, int &y) {
		if (o == 0) { x = y = 0; return; }
		if (tr[tr[o].ls].siz < k) {
			x = o;
			split(tr[o].rs, k - tr[tr[o].ls].siz - 1, tr[o].rs, y);
		} else {
			y = o;
			split(tr[o].ls, k, x, tr[o].ls);
		}
		pushup(o);
	}

	int merge(int x, int y) {
		if (x == 0 || y == 0) { return x + y; }
		if (tr[x].rd < tr[y].rd) {
			// std::cout << "x!!!\n";
			tr[x].rs = merge(tr[x].rs, y);
			pushup(x);
			return x;
		} else {
			// std::cout << "y!!!\n";
			tr[y].ls = merge(x, tr[y].ls);
			pushup(y);
			return y;
		}
	}

	int orkey(int o) {
		int ret = tr[tr[o].ls].siz + 1;
		while (tr[o].fa) {
			if (o == tr[tr[o].fa].rs)
				ret += tr[tr[tr[o].fa].ls].siz + 1;
			o = tr[o].fa;
		}
		return ret;
	}
} trp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("2596.in", "r", stdin);

	trp.tr[0].siz = trp.tr[0].val = trp.tr[0].fa = 0;
	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		pos[a[i]] = trp.newnode(a[i]);
		trp.rt = trp.merge(trp.rt, pos[a[i]]);
	}

	int u, v, w, x, y, z, t, i1, i2;
	for (int i = 1; i <= m; i++) {
		std::string s;
		u = v = w = x = y = z = t = 0;
		std::cin >> s;
		// std::cout << s << "\n";
		if (s == "Top") {
			// std::cout << s << "\n";
			std::cin >> x;
			u = trp.orkey(pos[x]);
			trp.split(trp.rt, u - 1, w, z);
			trp.split(z, 1, y, v);
			trp.rt = trp.merge(trp.merge(y, w), v);
		}
		if (s == "Bottom") {
			// std::cout << s << "\n";
			std::cin >> x;
			u = trp.orkey(pos[x]);
			trp.split(trp.rt, u - 1, w, z);
			trp.split(z, 1, y, v);
			trp.rt = trp.merge(trp.merge(w, v), y);
		}
		if (s == "Insert") {
			// std::cout << s << "\n";
			std::cin >> x >> y;
			if (y) {
				u = trp.orkey(pos[x]);
				trp.split(trp.rt, u - 1, w, v);
				trp.split(v, 1, t, z);
				if (y == 1) {
					trp.split(w, u - 2, i1, i2);
					trp.rt = trp.merge(trp.merge(trp.merge(i1, t), i2), z);
				} else {
					trp.split(z, 1, i1, i2);
					trp.rt = trp.merge(trp.merge(trp.merge(w, i1), t), i2);
				}
			}
		}
		if (s == "Ask") {
			// std::cout << s << "\n";
			std::cin >> x;
			std::cout << trp.orkey(pos[x]) - 1 << "\n";
		}
		if (s == "Query") {
			// std::cout << s << "\n";
			std::cin >> x;
			trp.split(trp.rt, x - 1, w, z);
			trp.split(z, 1, y, v);
			std::cout << trp.tr[y].val << "\n";
			trp.rt = trp.merge(trp.merge(w, y), v);
		}
	}
	return 0;
}
