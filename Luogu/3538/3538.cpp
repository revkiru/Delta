#include <bits/stdc++.h>

#define int long long

constexpr int N = 5e5 + 7;
constexpr int P1 = 12060529;
constexpr int P2 = 20090313;

int n, q;
int g[N], pw[N], hsh[N];
bool vis[N];
std::string s;
std::vector<int> pri;

void eulerSieve() {
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pri.push_back(i);
            g[i] = i;
        }
        for (size_t j = 0; j < pri.size() && pri[j] * i <= n; j++) {
            vis[pri[j] * i] = 1;
            g[pri[j] * i] = pri[j];
            if (i % pri[j] == 0)
                break;
        }
    }
}

void init() {
    eulerSieve();
    pw[0] = 1;
    for (int i = 1; i <= n; i++)
        pw[i] = (pw[i - 1] * 29) % P1 % P2;
    for (int i = 1; i <= n; i++)
        hsh[i] = (hsh[i - 1] * 29 + (s[i] - 'a' + 1)) % P1 % P2;
}

int calcHash(int l, int r) {
    return ((hsh[r] - hsh[l - 1] * pw[r - l + 1]) % P1 % P2 + P1 + P2) % P1 % P2;
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    std::cin >> s;
    s = '$' + s;
    init();
    // for (int i = 1; i <= n; i++)
    //     std::cout << pw[i] << " " << hsh[i] << "\n";
    std::cin >> q;
    while (q--) {
        int l, r, len, ans;
        std::cin >> l >> r;
        ans = len = r - l + 1;
        if (calcHash(l + 1, r) == calcHash(l, r - 1)) { std::cout << "1\n"; continue; }
        // int t0t = 0;
        while (len > 1) {
            // std::cout << t0t++ << "\n";
            if (calcHash(l + ans / g[len], r) == calcHash(l, r - ans / g[len]))
                ans /= g[len];
            len /= g[len];
        }
        std::cout << ans << "\n";
    }
    return 0;
}
