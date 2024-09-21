#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = ((int) 1e5 << 3) + 7;

int n;
int a[N], b[N];

struct SparseTable {
    int lg2[N], rmax[20][N];

    void init() {
        for (int i = 2; i <= n * 3; i++)
            lg2[i] = lg2[i >> 1] + 1;
        for (int i = 1; i <= n; i++)
            rmax[0][i] = rmax[0][i + n] = rmax[0][i + 2 * n] = a[i];
        for (int i = 1; (1 << i) <= n * 3; i++) {
            for (int j = 1; j <= n * 3 - (1 << i) + 1; j++) {
                rmax[i][j] = std::max(rmax[i - 1][j], rmax[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query_max(int l, int r) {
        int x = lg2[r - l + 1];
        return std::max(rmax[x][l], rmax[x][r - (1 << x) + 1]);
    }
} st;

bool check(int mid, int i, int x) {
    return (std::max(st.query_max(i - mid, i - 1), st.query_max(i + 1, i + mid)) >= x);
}

int binarySearch(int x, int i) {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid, i, x))
            r = mid;
        else
            l = mid + 1;
    }
    return (l == n) ? -1 : l;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    st.init();
    for (int i = 1; i <= n; i++) {
        std::cin >> b[i];
        int apos = binarySearch(b[i], i + n);
        std::cout << apos << " ";
    }
    std::cout << "\n";
    return 0;
}
