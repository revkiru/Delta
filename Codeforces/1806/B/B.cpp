#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n;
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

std::unordered_map<int, int, custom_hash> mp;

void solve() {
    mp.clear();
    std::cin >> n;
    for (int i = 1, inp; i <= n; i++) {
        std::cin >> inp;
        mp[inp]++;
    }

    if (mp[0] <= (n + 1) >> 1) {
        std::cout << "0\n";
    } else if (mp[0] + mp[1] < n) {
        std::cout << "1\n";
    } else if (mp[1] == 0) {
        std::cout << "1\n";
    } else {
        std::cout << "2\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // freopen("arrange.in", "r", stdin);
    // freopen("arrange.out", "w", stdout);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
