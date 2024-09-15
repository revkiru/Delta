#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;
constexpr int V = 40;

int n, m, sum;
int a[N], dvi[V], cot[V];
std::map<int, int> mp;

void init() {
    sum = 0;
    mp.clear();
    memset(cot, 0, sizeof(cot));
    memset(dvi, 0, sizeof(dvi));
}

int solve(int x) {
    for (int i = 0; i <= 32; i++)
        if ((x >> i) & 1ll)
            dvi[i] = 1;
    int ret = 0, lst = -1;
    for (int i = 0; i <= 32; i++) {
        if (lst != -1 && cot[i]) {
            cot[i]--;
            ret += (i - lst);
            lst = -1;
        }
        if (dvi[i]) {
            if (cot[i]) cot[i]--;
            else if (lst == -1) lst = i;
        }
        cot[i + 1] += (cot[i] >> 1ll);
        cot[i] = cot[i] & 1ll;
    }
    return ret;
}

void work() {
    std::cin >> n >> m;
    for (int i = 0; i <= 32; i++)
        mp[(1ll << i)] = i;
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i];
        cot[mp[a[i]]]++;
        sum += a[i];
    }
    sum -= n;
    if (sum < 0) { std::cout << "-1\n"; return; }
    std::cout << solve(sum) << "\n";
}

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        init();
        work();
    }
    return 0;
}
