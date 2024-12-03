#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int M = 1e6 + 7;

int n, m, ret;
int a[N];
std::set<int> st[M];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        ret += a[i] != a[i - 1];
        st[a[i]].insert(i);
    }
    for (int i = 1, opt, x, y; i <= m; i++) {
        std::cin >> opt;
        if (opt == 1) {
            std::cin >> x >> y;
            if (x == y)
                continue;
            if (st[x].size() > st[y].size())
                std::swap(st[x], st[y]);
            for (auto i : st[x])
                ret -= st[y].count(i - 1) + st[y].count(i + 1);
            for (auto i : st[x])
                st[y].insert(i);
            st[x].clear();
        }
        if (opt == 2)
            std::cout << ret << "\n";
    }
    return 0;
}
