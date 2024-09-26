#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, k, ans1;
int a[N];

struct SparseTable {
    int lg2[N], rmax[20][N], rmin[20][N];

    void init() {
        for (int i = 2; i <= n; i++)
            lg2[i] = lg2[i >> 1] + 1;
        for (int i = 1; i <= n; i++)
            rmax[0][i] = rmin[0][i] = a[i];
        for (int i = 1; (1 << i) <= n; i++) {
            for (int j = 1; j <= n - (1 << i) + 1; j++) {
                rmax[i][j] = std::max(rmax[i - 1][j], rmax[i - 1][j + (1 << (i - 1))]);
                rmin[i][j] = std::min(rmin[i - 1][j], rmin[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query_max(int l, int r) {
        int x = lg2[r - l + 1];
        return std::max(rmax[x][l], rmax[x][r - (1 << x) + 1]);
    }

    int query_min(int l, int r) {
        int x = lg2[r - l + 1];
        return std::min(rmin[x][l], rmin[x][r - (1 << x) + 1]);
    }
} st;

bool check(int x) {
    int cnt = 0;
    for (int i = 1; i <= n - x + 1; i++) {
        int mx = st.query_max(i, i + x - 1);
        int mn = st.query_min(i, i + x - 1);
        if (mx - mn >= ans1)
            cnt++;
    }
    return (cnt >= k);
}

void solve() {
    std::cin >> n >> k;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    ans1 = 2e9;
    st.init();
    for (int i = 1; i <= k; i++)
        ans1 = std::min(ans1, st.query_max(i, n - k + i) - st.query_min(i, n - k + i));
    std::cout << ans1 << " ";
    int l = 1, r = n, ans2;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (!check(mid))
            l = mid;
        else {
            r = mid - 1;
            ans2 = mid;
        }
    }
    std::cout << ans2 << "\n";
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
