#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n), cnt(3);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }

    std::vector<int> vp[3][3];
    std::vector<std::pair<int, int>> sp;
    auto Pos = [&](int idx) {
        if (idx < cnt[0]) return 0;
        if (idx < cnt[0] + cnt[1]) return 1;
        return 2;
    };
    auto AddBack = [&](int idx) { vp[a[idx]][Pos(idx)].push_back(idx); };
    auto RemoveBack = [&](int idx) { vp[a[idx]][Pos(idx)].pop_back(); };
    auto MySwap = [&](int i, int j) { sp.push_back({i, j}); RemoveBack(i); RemoveBack(j); std::swap(a[i], a[j]); AddBack(i); AddBack(j); };
    auto Fix = [&](int x) {
        while (!vp[1][x].empty() || !vp[2 - x][x].empty()) {
            if (vp[1][x].empty()) {
                if (!vp[1][2 - x].empty())
                    MySwap(vp[2 - x][x].back(), vp[1][2 - x].back());
                else
                    MySwap(vp[2 - x][x].back(), vp[1][1].back());
            }
            if (!vp[x][1].empty())
                MySwap(vp[1][x].back(), vp[x][1].back());
            else
                MySwap(vp[1][x].back(), vp[x][2 - x].back());
        }
    };

    for (int i = 0; i < n; i++)
        AddBack(i);
    if (cnt[0] <= cnt[2]) {
        Fix(0);
        Fix(2);
    } else {
        Fix(2);
        Fix(0);
    }

    std::cout << sp.size() << "\n";
    for (auto [i, j] : sp) {
        std::cout << i + 1 << " " << j + 1 << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
