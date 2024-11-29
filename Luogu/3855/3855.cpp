#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, m, rt, tx, ty, tz;
int rot[N];

struct node {
	i64 val;
	int rd, siz, ls, rs;
};

struct Treap {
	int tim;
	node tr[N * 50];

	#define ls(o) (tr[o].ls)
	#define rs(o) (tr[o].rs)

	int newnode(i64 x = 0) {
		tr[++tim].val = x; tr[tim].siz = 1; tr[tim].rd = myrand();
		return tim;
	}

	int clone(int now) {
		tr[++tim] = tr[now];
		return tim;
	}

	void pushup(const int o) {
		tr[o].siz = 1;
		if (ls(o))
			tr[o].siz += tr[ls(o)].siz;
		if (rs(o))
			tr[o].siz += tr[rs(o)].siz;
	}

	int merge(int x, int y) {
		if (!x || !y) { return x + y; }
		if (tr[x].rd < tr[y].rd) {
			x = clone(x);
			rs(x) = merge(rs(x), y);
			pushup(x);
			return x;
		} else {
			y = clone(y);
			ls(y) = merge(x, ls(y));
			pushup(y);
			return y;
		}
	}

	void split(int o, i64 k, int &x, int &y) {
		if (!o) { x = y = 0; return; }
		if (tr[o].val <= k) {
			x = clone(o);
			split(rs(x), k, rs(x), y);
			pushup(x);
		} else {
			y = clone(o);
			split(ls(y), k, x, ls(y));
			pushup(y);
		}
	}

	int kth(int o, i64 k) {
		while (1) {
			if (tr[ls(o)].siz >= k)
				o = ls(o);
			else if (tr[ls(o)].siz + 1 == k)
				return o;
			else {
				k -= tr[ls(o)].siz + 1;
				o = rs(o);
			}
		}
	}
} trp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
    for (int i = 1; i <= n; i++) {
    	int q, s;
    	i64 a;
    	tx = ty = tz = 0;

    	std::cin >> q >> s >> a;
    	rot[i] = rot[q];
        if (s == 1) {
            trp.split(rot[i], a, tx, ty);
            rot[i] = trp.merge(trp.merge(tx, trp.newnode(a)), ty);
            // std::cout << s << " " << rot[i] << "!!!\n";
        }
        if (s == 2) {
            trp.split(rot[i], a, tx, tz);
            trp.split(tx, a - 1, tx, ty);
            ty = trp.merge(trp.tr[ty].ls, trp.tr[ty].rs);
            rot[i] = trp.merge(trp.merge(tx, ty), tz);
            // std::cout << s << " " << rot[i] << "!!!\n";
        }
        if (s == 3) {
        	trp.split(rot[i], a - 1, tx, ty);
            std::cout << trp.tr[tx].siz + 1 << "\n";
            rot[i] = trp.merge(tx, ty);
            // std::cout << s << " " << rot[i] << "!!!\n";
        }
        if (s == 4) {
            std::cout << trp.tr[trp.kth(rot[i], a)].val << "\n";
        }
        if (s == 5) {
            trp.split(rot[i], a - 1, tx, ty);
            if (!tx) { std::cout << "-2147483647\n"; continue; }
            std::cout << trp.tr[trp.kth(tx, trp.tr[tx].siz)].val << "\n";
            rot[i] = trp.merge(tx, ty);
            // std::cout << s << " " << rot[i] << "!!!\n";
        }
        if (s == 6) {
            trp.split(rot[i], a, tx, ty);
            if (!ty) { std::cout << "2147483647\n"; continue; }
            std::cout << trp.tr[trp.kth(ty, 1)].val << "\n";
            rot[i] = trp.merge(tx, ty);
            // std::cout << s << " " << rot[i] << "!!!\n";
        }
    }
    return 0;
}
