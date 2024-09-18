#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int L = 1e6;
constexpr int V = 1e9;

int n, j;
i64 _x, _y;
std::map<i64, i64> mp;

void solve() {
    mp.clear();

    std::cin >> n;
    for (int i = 1, x; i <= n; i++) {
        std::cin >> x;
        ++mp[x];
    }

    i64 ret = 0;
    for (auto &i : mp) {
        _x = i.first, _y = i.second;
        ret += _y * (_y - 1) * (_y - 2);
        if (_x < L) {
            for (j = 1; j * j < _x; j++) {
                if (j != 1 && (_x % j == 0) && mp.count(_x / j) && mp.count(_x * j))
                    ret += mp[_x / j] * _y * mp[_x * j];
                if (_x % j == 0 && mp.count(j) && mp.count(_x / j * _x))
                    ret += mp[j] * _y * mp[_x / j * _x];
            }
            if (j != 1 && j * j == _x && mp.count(j) && mp.count(_x * j))
                ret += mp[j] * _y * mp[_x * j];
        } else {
            for (j = 2; _x * j <= V; j++) {
                if (_x % j == 0 && mp.count(_x / j) && mp.count(_x * j))
                    ret += mp[_x / j] * _y * mp[_x * j];
            }
        }
    }
    std::cout << ret << "\n";
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
