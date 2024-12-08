#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n;

struct line {
	double k, b;
} p[N << 1];

struct LiChaoTree {
	int t0t, tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	double calc(int idx, int x) { return (x - 1) * p[idx].k + p[idx].b; }

    void add(double b, double k) {
        t0t++;
        p[t0t].b = b;
        p[t0t].k = k;
    }

	void modify(int o, int l, int r, int x) {
        if (l == r) {
            if (calc(x, l) > calc(tr[o], l))
                tr[o] = x;
            return;
        }
        int mid = (l + r) >> 1;
        if (p[tr[o]].k < p[x].k) {
            if (calc(x, mid) > calc(tr[o], mid)) {
                modify(ls(o), l, mid, tr[o]);
                tr[o] = x;
            } else
                modify(rs(o), mid + 1, r, x);
        }
        if (p[tr[o]].k > p[x].k) {
            if (calc(x, mid) > calc(tr[o], mid)) {
                modify(rs(o), mid + 1, r, tr[o]);
                tr[o] = x;
            } else
                modify(ls(o), l, mid, x);
        }
    }

    double query(int o, int l, int r, int x) {
        if (l == r) return calc(tr[o], x);
        int mid = (l + r) >> 1;
        if (x <= mid)
            return std::max(calc(tr[o], x), query(ls(o), l, mid, x));
        else
            return std::max(calc(tr[o], x), query(rs(o), mid + 1, r, x));
    }
} lcTr;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string opt;
        double s, p, t;
        std::cin >> opt;
        if (opt == "Project") {
            // std::cout << i << "...\n";
            std::cin >> s >> p;
            lcTr.add(s, p);
            lcTr.modify(1, 1, N, lcTr.t0t);
        } else {
            // std::cout << i << "!!!\n";
            std::cin >> t;
            std::cout << int(lcTr.query(1, 1, N, t) / 100) << "\n";
        }
    }
    return 0;
}
