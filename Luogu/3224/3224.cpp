#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, _q;

std::pair<int, int> q[N];

struct DSU {
    int fa[N];

    int find(int x) { return (fa[x] == x ? x : fa[x] = find(fa[x])); }

    void unite(int x, int y) {
        x = find(x), y = find(y);
        fa[x] = y;
    }
} uni;

__gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type, std::greater<std::pair<int, int>>,
                    __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> tr[N];

void build(int n) {
    for (int i = 1; i <= n; i++)
        tr[uni.find(i)].insert(q[i]);
}

void MergeRB(int x, int y) {
    x = uni.find(x), y = uni.find(y);
    if (x == y)
        return;
    if (tr[x].size() > tr[y].size())
        std::swap(tr[x], tr[y]);
    for (auto i : tr[x])
        tr[y].insert(i);
    tr[x].clear();
    uni.fa[x] = y;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        std::cin >> q[i].first;
        q[i].second = i;
        uni.fa[i] = i;
    }
    for (int i = 1, x, y; i <= m; i++) {
        std::cin >> x >> y;
        uni.unite(x, y);
    }

    build(n);
    std::cin >> _q;
    while (_q--) {
        char opt;
        int x, y;
        std::cin >> opt >> x >> y;
        if (opt == 'B')
            MergeRB(x, y);
        else {
            x = uni.find(x);
            if (y > tr[x].size())
                std::cout << "-1\n";
            else
                std::cout << (*tr[x].find_by_order(tr[x].size() - y)).second << "\n";
        }
    }
    return 0;
}
