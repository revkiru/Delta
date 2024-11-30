#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, rot[N];
int lstAns;

struct node {
	int val, rd, siz, rev, ls, rs;
	int sum;
};

struct Treap {
	int tim, x, y, z;
	node tr[N << 8];

	#define ls(o) (tr[o].ls)
	#define rs(o) (tr[o].rs)

	int newnode(int x) {
		tr[++tim].val = x; tr[tim].sum = x; tr[tim].siz = 1; tr[tim].rd = myrand();
		return tim;
	}

	int clone(int now) {
		tr[++tim] = tr[now];
		return tim;
	}

	void pushup(const int o) {
		tr[o].siz = tr[ls(o)].siz + tr[rs(o)].siz + 1;
		tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum + tr[o].val;
	}

	void pushdown(int o) {
		if (tr[o].rev) {
			if (ls(o)) { ls(o) = clone(ls(o)); tr[ls(o)].rev ^= 1; }
			if (rs(o)) { rs(o) = clone(rs(o)); tr[rs(o)].rev ^= 1; }
			std::swap(ls(o), rs(o));
			tr[o].rev = 0;
		}
	}

	void split(int o, int k, int &x, int &y) {
		if (!o) { x = y = 0; return; }
		pushdown(o);
		if (tr[ls(o)].siz < k) {
			x = clone(o);
			split(rs(x), k - tr[ls(x)].siz - 1, rs(x), y);
			pushup(x);
		} else {
			y = clone(o);
			split(ls(y), k, x, ls(y));
			pushup(y);
		}
	}

	int merge(int x, int y) {
		if (!x || !y) { return x + y; }
		if (tr[x].rd < tr[y].rd) {
			pushdown(x);
			x = clone(x);
			rs(x) = merge(rs(x), y);
			pushup(x);
			return x;
		} else {
			pushdown(y);
			y = clone(y);
			ls(y) = merge(x, ls(y));
			pushup(y);
			return y;
		}
	}

	int query(int &o, int l, int r) {
		split(o, l - 1, x, y);
		split(y, r - l + 1, y, z);
		int ret = tr[y].sum;
		o = merge(x, merge(y, z));
		return ret;
	}

	void flip(int &o, int l, int r) {
		split(o, l - 1, x, y);
		split(y, r - l + 1, y, z);
		tr[y].rev ^= 1;
		o = merge(x, merge(y, z));
	}

	void insert(int &o, int p, int k) {
		split(o, p, x, y);
		o = merge(merge(x, newnode(k)), y);
	}

	void remove(int &o, int k) {
		split(o, k, x, z);
		split(x, k - 1, x, y);
		o = merge(x, z);
	}
} trp;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, s, opt, x, y; i <= n; i++) {
		std::cin >> s >> opt >> x;
		x ^= lstAns;
		if (opt != 2) { std::cin >> y; y ^= lstAns; }

		rot[i] = rot[s];
		if (opt == 1)
			trp.insert(rot[i], x, y);
		if (opt == 2)
			trp.remove(rot[i], x);
		if (opt == 3)
			trp.flip(rot[i], x, y);
		if (opt == 4) {
			lstAns = trp.query(rot[i], x, y);
			std::cout << lstAns << "\n";
		}
	}
	return 0;
}
