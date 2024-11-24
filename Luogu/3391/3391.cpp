#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, m;

struct node {
    int rd, siz, val, lzy, ls, rs;
};

struct FHQ_Treap {
    int tim, rt, l, r, mid, sum;
    node tr[N << 1];

    int newnode(int x) {
        tim++;
        tr[tim].val = x; tr[tim].siz = 1; tr[tim].rd = myrand();
        return tim;
    }

    void pushup(int o) {
        tr[o].siz = tr[tr[o].ls].siz + tr[tr[o].rs].siz + 1;
    }

    void pushdown(int o) {
    	std::swap(tr[o].ls, tr[o].rs);
    	tr[tr[o].ls].lzy ^= 1;
    	tr[tr[o].rs].lzy ^= 1;
    	tr[o].lzy = 0;
    }

    void split(int o, int k, int &x, int &y) {
        if (o == 0) { x = y = 0; return; }
        if (tr[o].lzy) { pushdown(o); }
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
        	if (tr[x].lzy) { pushdown(x); }
            tr[x].rs = merge(tr[x].rs, y);
            pushup(x);
            return x;
        } else {
        	if (tr[y].lzy) { pushdown(y); }
            tr[y].ls = merge(x, tr[y].ls);
            pushup(y);
            return y;
        }
    }

    void insert(int x) {
        split(rt, x, l, r);
        rt = merge(merge(l, newnode(x)), r);
    }

    void reverse(int x, int y) {
    	split(rt, x - 1, l, r);
		split(r, y - x + 1, r, mid);
		tr[r].lzy ^= 1;
		rt = merge(l, merge(r, mid));
    }

    void dfs(int o) {
    	if (tr[o].lzy) { pushdown(o); }
    	if (tr[o].ls) {dfs(tr[o].ls); }
    	std::cout << tr[o].val << " ";
    	if (tr[o].rs) { dfs(tr[o].rs); }
    }
} trp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		trp.insert(i);
	}
	for (int i = 1, x, y; i <= m; i++) {
		std::cin >> x >> y;
		trp.reverse(x, y);
	}
	trp.dfs(trp.rt);
	return 0;
}
