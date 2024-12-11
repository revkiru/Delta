#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e6 + 7;
constexpr int A = 3e5 + 7;
constexpr int P = 1e9 + 7; 
constexpr int R = 3e6;

int n, q, cnt, ans;
int a[A];

std::random_device rdv;
std::mt19937 myrand(rdv());

struct PersistentTreap {
	int rcnt, rt;

	struct node {
		int ls, rs, siz, rd;
		int val, sum, add, cov;
		bool rev;
	} tr[N];
	
	#define ls(o) (tr[o].ls)
	#define rs(o) (tr[o].rs)

	int newnode(int x) {
		tr[++rcnt].rd = myrand();
		tr[rcnt].cov = -1;
		tr[rcnt].siz = 1;
        tr[rcnt].rev = 0;
        tr[rcnt].add = ls(rcnt) = rs(rcnt) = 0;
		tr[rcnt].sum = tr[rcnt].val = x;
		return rcnt;
	}
	
	int clone(int o) {
		tr[++rcnt] = tr[o];
		return rcnt;
	}
	
	void rangeCover(int o, int x) {
		tr[o].val = x;
		tr[o].sum = 1ll * tr[o].siz * x % P;
		tr[o].cov = x % P;
		tr[o].add = 0;
	}
	
	void rangeAdd(int o, int x) {
		tr[o].val = (1ll * tr[o].val + x) % P;
		tr[o].sum = (1ll * tr[o].sum + 1ll * tr[o].siz * x % P) % P;
		tr[o].add = (tr[o].add + x) % P;
	}
	
	void pushdown(int o) {
		if (!tr[o].rev && tr[o].cov == -1 && !tr[o].add) return;
		if (ls(o)) ls(o) = clone(ls(o));
		if (rs(o)) rs(o) = clone(rs(o));
		if (tr[o].rev) {
			if (ls(o)) tr[ls(o)].rev ^= 1;
			if (rs(o)) tr[rs(o)].rev ^= 1;
			std::swap(ls(o), rs(o));
			tr[o].rev = 0;
		}
		if (tr[o].cov != -1) {
			if (ls(o)) rangeCover(ls(o), tr[o].cov);
			if (rs(o)) rangeCover(rs(o), tr[o].cov);
			tr[o].cov = -1;
		}
		if (tr[o].add) {
			if (ls(o)) rangeAdd(ls(o), tr[o].add);
			if (rs(o)) rangeAdd(rs(o), tr[o].add);
			tr[o].add = 0; 
		}
	}
	
	void pushup(const int o) {
		tr[o].siz = tr[ls(o)].siz + tr[rs(o)].siz + 1;
		tr[o].sum = (1ll * tr[ls(o)].sum + tr[rs(o)].sum + tr[o].val) % P;
	}
	
	void split(int o, int k, int &x, int &y) {
		if (!o) { x = y = 0; return; }
		pushdown(o);
		if (tr[ls(o)].siz >= k) {
			y = clone(o);
			split(ls(o), k, x, ls(y));
			pushup(y);
		} else {
			x = clone(o);
			split(rs(o), k - tr[ls(o)].siz - 1, rs(x), y);
			pushup(x);
		}
	}
	
	int merge(int x, int y) {
		if (!x || !y) return x | y;
		if (tr[x].rd < tr[y].rd) {
			x = clone(x);
			pushdown(x);
			rs(x) = merge(rs(x), y);
			pushup(x);
			return x;
		} else {
			y = clone(y);
			pushdown(y);
			ls(y) = merge(x, ls(y));
			pushup(y);
			return y;
		}
	}
	
	int build(int l, int r) {
		if (l > r) return 0;
		int mid = (l + r) >> 1;
		int o = newnode(a[mid]);
		ls(o) = build(l, mid - 1);
		rs(o) = build(mid + 1, r);
		pushup(o);
		return o; 
	} 
	
	void dfs(int o) {
		pushdown(o);
		if (ls(o)) dfs(ls(o));
		a[++cnt] = tr[o].val;
		if (rs(o)) dfs(rs(o));
	}
	
	int query(int l, int r) {
		int x, y, z, ans;
		split(rt, r, x, z);
		split(x, l - 1, x, y);
		ans = tr[y].sum;
		rt = merge(merge(x, y), z);
		return ans;
	} 
	
	void trCover(int l, int r, int k) {
		int x, y, z;
		split(rt, r, x, z);
		split(x, l - 1, x, y);
		y = clone(y);
		rangeCover(y, k);
		rt = merge(merge(x, y), z);
	}
	
	void trAdd(int l, int r, int k) {
		int x, y, z;
		split(rt, r, x, z);
		split(x, l - 1, x, y);
		y = clone(y);
		rangeAdd(y, k);
		rt = merge(merge(x, y), z); 
	} 
	
	void trCopy(int l1, int r1, int l2, int r2) {
		int flg = 0;
		if (l1 > l2) { std::swap(l1, l2); std::swap(r1, r2); flg = 1; }
		int o1, o2, o3, o4, o5;
		split(rt, r2, o1, o5);
		split(o1, l2 - 1, o1, o4);
		split(o1, r1, o1, o3);
		split(o1, l1 - 1, o1, o2);
		if (flg) o2 = clone(o4);
		else o4 = clone(o2);
		rt = merge(merge(merge(merge(o1, o2), o3), o4), o5);
	}
	
	void trSwap(int l1, int r1, int l2, int r2) {
		if (l1 > l2) { std::swap(l1, l2); std::swap(r1, r2); }
		int o1, o2, o3, o4, o5;
		split(rt, r2, o1, o5);
		split(o1, l2 - 1, o1, o4);
		split(o1, r1, o1, o3);
		split(o1, l1 - 1, o1, o2);
		o2 = clone(o2);
		o4 = clone(o4);
		std::swap(o2, o4);
		rt = merge(merge(merge(merge(o1, o2), o3), o4), o5);
	}
	
	void trFlip(int l, int r) {
		int x, y, z;
		split(rt, r, x, z);
		split(x, l - 1, x, y);
		y = clone(y);
		tr[y].rev ^= 1;
		rt = merge(merge(x, y), z);
	}
} trp;

int main() {
	scanf("%d %d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);

    trp.rt = trp.build(1, n);
    trp.dfs(trp.rt);
    for (int i = 1, opt, l, r, _l, _r, k; i <= q; i++) {
        scanf("%d %d %d", &opt, &l, &r);
        switch (opt) {
            case 1:
                ans = trp.query(l, r);
                printf("%d\n", ans);
                break;
            case 2:
                scanf("%d", &k);
                trp.trCover(l, r, k);
                break;
            case 3:
                scanf("%d", &k);
                trp.trAdd(l, r, k);
                break;
            case 4:
                scanf("%d %d", &_l, &_r);
                trp.trCopy(l, r, _l, _r);
                break;
            case 5:
                scanf("%d %d", &_l, &_r);
                trp.trSwap(l, r, _l, _r);
                break;
            case 6:
                trp.trFlip(l, r);
                break;
            default:
                break;
        }

        if (trp.rcnt > R) {
            cnt = 0;
            trp.dfs(trp.rt);
            trp.rt = trp.rcnt = 0;
            trp.rt = trp.build(1, n);
        }
    }

    cnt = 0;
    trp.dfs(trp.rt);
    for (int i = 1; i <= n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
