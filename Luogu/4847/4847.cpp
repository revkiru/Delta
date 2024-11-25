#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, m;

struct node {
	int rd, siz, ls, rs, fa;
	i64 val, sum;
};

struct FHQ_Treap {
	int tim, rt, l, r, mid;
	node tr[N << 1];

	#define ls(o) (tr[o].ls)
	#define rs(o) (tr[o].rs)

	int newnode(int x) {
		tr[++tim].val = x;
		tr[tim].sum = tr[tim].val;
		tr[tim].rd = myrand();
		tr[tim].siz = 1;
		tr[tim].fa = tim;
		return tim;
	}

	void pushup(int o) {
		tr[o].siz = tr[ls(o)].siz + tr[rs(o)].siz + 1;
		tr[o].sum = tr[ls(o)].sum + tr[rs(o)].sum + tr[o].val;
		if (ls(o))
			tr[ls(o)].fa = o;
		if (rs(o))
			tr[rs(o)].fa = o;
	}

	void split(int o, int k, int &x, int &y) {
		if (!o) { x = y = 0; return; }
		if (tr[ls(o)].siz < k) {
			x = o;
			split(rs(o), k - tr[ls(o)].siz - 1, rs(o), y);
		} else {
			y = o;
			split(ls(o), k, x, ls(o));
		}
		tr[x].fa = x, tr[y].fa = y;
		pushup(o);
	}

	int merge(int x, int y) {
		if (!x || !y) { return x | y; }
		if (tr[x].rd < tr[y].rd) {
			rs(x) = merge(rs(x), y);
			pushup(x);
			return x;
		} else {
			ls(y) = merge(x, ls(y));
			pushup(y);
			return y;
		}
	}

	int rank(int o) {
		int ret = tr[ls(o)].siz + 1;
		while (tr[o].fa ^ o) {
			if (rs(tr[o].fa) == o)
				ret += tr[ls(tr[o].fa)].siz + 1;
			o = tr[o].fa;
		}
		return ret;
	}
} trp;

int find(int x) { return (trp.tr[x].fa == x) ? x : find(trp.tr[x].fa); }

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		trp.newnode(x);
	}
	for (int i = 1, a, b; i <= m; i++) {
		char opt;
		std::cin >> opt;
		if (opt == 'M') {
			std::cin >> a >> b;
			int fa = find(a), fb = find(b);
			if (fa != fb) {
				trp.merge(fb, fa);
			}
		}
		if (opt == 'D') {
			std::cin >> a;
			int fa = find(a), x = 0, y = 0;
			trp.split(fa, trp.rank(a) - 1, x, y);
		}
		if (opt == 'Q') {
			std::cin >> a >> b;
			int fa = find(a), fb = find(b);
			if (fa != fb) {
				std::cout << "-1\n";
			} else {
				int l = trp.rank(a), r = trp.rank(b);
				if (l > r)
					std::swap(l, r);
				int x = 0, y = 0, z = 0;
				trp.split(fa, r, x, z);
				trp.split(x, l - 1, x, y);
				std::cout << trp.tr[y].sum << "\n";
				fa = trp.merge(trp.merge(x, y), z);
			}
		}
	}
	return 0;
}
