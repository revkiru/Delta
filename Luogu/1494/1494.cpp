#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e4 + 7;

int n, m, unt;
int c[N], cnt[N];
i64 sum;
i64 ans1[N], ans2[N];

struct ques {
    int l, r, id;

    bool operator < (const ques &x) const {
        if (l / unt != x.l / unt) return l < x.l;
        if ((l / unt) & 1) return r < x.r;
        return r > x.r;
    }
} a[N];

void add(int i) {
    sum += cnt[i];
    cnt[i]++;
}

void del(int i) {
    cnt[i]--;
    sum -= cnt[i];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    unt = std::sqrt(n);
    for (int i = 1; i <= n; i++)
        std::cin >> c[i];
    for (int i = 1; i <= m; i++) {
        std::cin >> a[i].l >> a[i].r;
        a[i].id = i;
    }
    std::sort(a + 1, a + m + 1);
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        if (a[i].l == a[i].r) {
            ans1[a[i].id] = 0;
            ans2[a[i].id] = 1;
            continue;
        }
        while (l > a[i].l) add(c[--l]);
        while (r < a[i].r) add(c[++r]);
        while (l < a[i].l) del(c[l++]);
        while (r > a[i].r) del(c[r--]);
        ans1[a[i].id] = sum;
        ans2[a[i].id] = 1ll * (r - l + 1) * (r - l) >> 1;
    }
    for (int i = 1; i <= m; i++) {
        if (ans1[i] != 0) {
            i64 _g = std::__gcd(ans1[i], ans2[i]);
            ans1[i] /= _g;
            ans2[i] /= _g;
        } else {
            ans2[i] = 1;
        }
        std::cout << ans1[i] << "/" << ans2[i] << "\n";
    }
    return 0;
}
