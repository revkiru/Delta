#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;
constexpr int M = 5e6 + 7;

int n, m, q, len;
int a[N], b[N], lsh[N];
int fa[N], ans[N];

struct edge {
    int u, v, w;

    friend bool operator < (const edge &x, const edge &y) {
        return x.w < y.w;
    }
} E[M];

struct ques {
    int v, x, k, id;

    friend bool operator < (const ques &a, const ques &b) {
        return a.x < b.x;
    }
} qs[N];

struct node {
    int siz, ls, rs;
};

struct SegTree {
    int rcnt, rt[N];
    node tr[N << 8];

    #define ls(o) (tr[o].ls)
    #define rs(o) (tr[o].rs)

    void insert(int &o, int l, int r, int p) {
        if (!o) o = ++rcnt;
        tr[o].siz++;
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (p <= mid)
            insert(ls(o), l, mid, p);
        else
            insert(rs(o), mid + 1, r, p);
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;
        tr[x].siz += tr[y].siz;
        ls(x) = merge(ls(x), ls(y));
        rs(x) = merge(rs(x), rs(y));
        return x;
    }
    
    int find(int o, int l, int r, int k) {
    	if (l == r) return l;
    	int mid = (l + r) >> 1;
    	if (tr[ls(o)].siz >= k)
    		return find(ls(o), l, mid, k);
    	else
    		return find(rs(o), mid + 1, r, k - tr[ls(o)].siz);
	}
} seg;

int find(int x) {
    return (fa[x] == x ? x : fa[x] = find(fa[x]));
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; i++) {
        int d = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
        seg.insert(seg.rt[i], 1, n, d);
        fa[i] = i;
    }

    for (int i = 1; i <= m; i++)
        std::cin >> E[i].u >> E[i].v >> E[i].w;
    std::sort(E + 1, E + m + 1);

    for (int i = 1; i <= q; i++) {
        std::cin >> qs[i].v >> qs[i].x >> qs[i].k;
        qs[i].id = i;
    }
    std::sort(qs + 1, qs + q + 1);

    for (int i = 1, p = 0; i <= q; i++) {
        while (E[p + 1].w <= qs[i].x && p < m) {
        	int x = find(E[p + 1].u), y = find(E[p + 1].v);
        	if (x != y) {
        		seg.merge(seg.rt[x], seg.rt[y]);
        		fa[y] = x;
			}
			p++;
		}
		int x = find(qs[i].v);
		if (seg.tr[seg.rt[x]].siz < qs[i].k)
			ans[qs[i].id] = -1;
		else
			ans[qs[i].id] = b[seg.find(seg.rt[x], 1, n, seg.tr[seg.rt[x]].siz - qs[i].k + 1)];
    }

    for (int i = 1; i <= q; i++)
        std::cout << ans[i] << "\n";
    return 0;
}
