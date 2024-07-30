#include <bits/stdc++.h>

#define int long long

constexpr int N = 2e5 + 7;
constexpr int R = 2e6;

int n, m;

struct Fenwick {
    int tr[R << 2];

    int lowbit(int x) { return x & -x; }

    void add(int x, int v) {
        for (; x <= R; x += lowbit(x))
            tr[x] += v;
    }

    int query(int x) {
        int res = 0;
        for (; x; x -= lowbit(x))
            res += tr[x];
        return res;
    }

    int sum(int l, int r) {
        return query(r) - query(l - 1);
    }
} bit;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    int flg = 0;
    for (int i = 1, inp; i <= n; i++) {
        std::cin >> inp;    
        int res = bit.query(R) - bit.query(inp - 1);
        flg ^= (res & 1);
        bit.add(inp, 1);
    }

    for (int i = 1; i <= m; i++) {
        int opt, l1, l2, r1, r2, k, x;
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> l1 >> r1 >> l2 >> r2;
            int ql = r1 + 1, qr = l2 - 1;
            flg ^= (((r1 - l1 + 1) * (r2 - l2 + 1) + (qr - ql + 1) * (r1 - l1 + 1) + (qr - ql + 1) * (r2 - l2 + 1)) & 1);
        }
        if (opt == 2) {
            std::cin >> l1 >> r1 >> k;
            int ql = r1 + 1, qr = k;
            flg ^= (((r1 - l1 + 1) * (qr - ql + 1)) & 1);
        }
        if (opt == 3) {
            std::cin >> x;
            flg ^= bit.sum(x, R) & 1;
            bit.add(x, 1);
        }
        if (opt == 4) {
            std::cin >> x;
            flg ^= bit.sum(1, x) & 1;
            bit.add(x, 1);
        }

        if (flg) std::cout << "odd\n";
        else std::cout << "even\n";
    }

    return 0;
}
