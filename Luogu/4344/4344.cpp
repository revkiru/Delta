#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;
constexpr double MAX_TIME = 0.8;

int n, m;

struct ODT {
    struct Node_t {
        int l, r;
        mutable int v;

        bool operator < (const Node_t &x) const {
            return l < x.l;
        }
    };
    std::set<Node_t> s;

    auto split(int p) {
        auto it = s.lower_bound({p, p, -1});
        if (it != s.end() && it->l == p)
            return it;
        it--;
        int l = it->l, r = it->r, v = it->v;
        s.erase(it);
        s.insert({l, p - 1, v});
        return s.insert({p, r, v}).first;
    }

    void assign(int l, int r, int v) {
        auto _r = split(r + 1);
        auto _l = split(l);
        s.erase(_l, _r);
        s.insert({l, r, v});
    }

    void perform(int x, int y, int l, int r) {
        auto _r = split(y + 1);
        auto _l = split(x);
        int sum = 0;
        for (auto it = _l; it != _r; it++)
            if (it->v)
                sum += (it->r - it->l + 1);
        assign(x, y, 0);

        _r = split(r + 1);
        _l = split(l);
        for (auto it = _l; it != _r; it++) {
            if (!(it->v)) {
                if (sum >= (it->r - it->l + 1)){
                    it->v = 1;
                    sum -= (it->r - it->l + 1);
                } else {
                    assign(it->l, it->l + sum - 1, 1);
                    sum = 0;
                }
            }
        }
    }

    int query(int l, int r) {
        auto _r = split(r + 1);
        auto _l = split(l);
        int res = 0, ans = 0;
        for (auto it = _l; it != _r; it++) {
            if (!(it->v))
                res += (it->r - it->l + 1);
            else {
                ans = std::max(ans, res);
                res = 0;
            }
        }
        return std::max(res, ans);
    }
} odt;

int main() {
    scanf("%d %d", &n, &m);
    odt.s.insert({1, n, 1});
    for (int _t = 1, opt, x, y, l, r; _t <= m; _t++) {
        scanf("%d %d %d", &opt, &x, &y);
        if (opt == 0) {
            odt.assign(x, y, 0);
        }
        else if (opt == 1) {
            scanf("%d %d", &l, &r);
            odt.perform(x, y, l, r);
        }
        else {
            if ((double) clock() / CLOCKS_PER_SEC > MAX_TIME) {
                printf("1\n");
                continue;
            }
            printf("%d\n", odt.query(x, y));
        }
    }
    return 0;
}
