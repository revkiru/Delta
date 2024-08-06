#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

struct node {
	int rd, siz, val, ls, rs;
};

struct FHQTreap {
	int t0t, rt, l, r, mid, sum;
	node tr[N << 1];

	int newnode(int x) {
		t0t++;
		tr[t0t].val = x;
		tr[t0t].siz = 1;
		tr[t0t].rd = myrand();
		return t0t;
	}

	void pushup(int o) {
		tr[o].siz = tr[tr[o].ls].siz + tr[tr[o].rs].siz + 1;
	}

	void split(int o, int k, int &x, int &y) {
		if (o == 0) { x = y = 0; return; }
		if (tr[o].val <= k) {
			x = o;
			split(tr[o].rs, k, tr[o].rs, y);
		} else {
			y = o;
			split(tr[o].ls, k, x, tr[o].ls);
		}
		pushup(o);
	}

	int merge(int x, int y) {
		if (x == 0 || y == 0) return x + y;
		if (tr[x].rd < tr[y].rd) {
			tr[x].rs = merge(tr[x].rs, y);
			pushup(x);
			return x;
		} else {
			tr[y].ls = merge(x, tr[y].ls);
			pushup(y);
			return y;
		}
	}

	void insert(int x) {
		split(rt, x, l, r);
		rt = merge(merge(l, newnode(x)), r);
	}

	void remove(int x) {
		split(rt, x, l, r);
		split(l, x - 1, l, mid);
		mid = merge(tr[mid].ls, tr[mid].rs);
		rt = merge(merge(l, mid), r);
	}

	int kth(int o, int k) {
		while (true) {
			if (k <= tr[tr[o].ls].siz)
				o = tr[o].ls;
			else {
				if (k == tr[tr[o].ls].siz + 1)
					return o;
				else {
					k -= tr[tr[o].ls].siz + 1;
					o = tr[o].rs;
				}
			}
		}
	}

	int rank(int k) {
		split(rt, k - 1, l, r);
		int ret = tr[l].siz + 1;
		rt = merge(l, r);
		return ret;
	}

	int query_pre(int k) {
		split(rt, k - 1, l, r);
		int ret = tr[kth(l, tr[l].siz)].val;
		rt = merge(l, r);
		return ret;
	}

	int query_suf(int k) {
		split(rt, k, l, r);
		int ret = tr[kth(r, 1)].val;
		rt = merge(l, r);
		return ret;
	}
} trp;

int n;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	while (n--) {
		int s, x;
		std::cin >> s >> x;
		if (s == 1) trp.insert(x);
		if (s == 2) trp.remove(x);
		if (s == 3) std::cout << trp.rank(x) << "\n";
		if (s == 4) std::cout << trp.tr[trp.kth(trp.rt, x)].val << "\n";
		if (s == 5) std::cout << trp.query_pre(x) << "\n";
		if (s == 6) std::cout << trp.query_suf(x) << "\n";
	}
	return 0;
}
