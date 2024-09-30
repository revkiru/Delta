#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;
constexpr int B = 600;

int n, m, unt;
i64 ans, ret;
int a[N], cnt[N], L[N], R[N];
std::pair<int, int> s[N];

struct ques {
    int l, r, id;
    bool operator < (const ques &x) const {
        if (l / unt != x.l / unt) return l < x.l;
        if ((l / unt) & 1) return r < x.r;
        return r > x.r;
    }
} q[N];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    unt = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        s[i] = {a[i], i};
    }
    std::sort(s + 1, s + n + 1);
    s[0].second = 0;
    s[n + 1].second = n + 1;
    for (int i = 1; i <= n; i++) {
        L[s[i].second] = s[i - 1].second;
        R[s[i].second] = s[i + 1].second;
        if (s[i].first - s[i - 1].first > s[i + 1].first - s[i].first && s[i + 1].second <= n)
            L[s[i].second] = 0;
        if (s[i].first - s[i - 1].first < s[i + 1].first - s[i].first && s[i - 1].second)
            R[s[i].second] = n + 1;
    }

    for (int i = 1; i <= m; i++) {
        std::cin >> q[i].l >> q[i].r;
        q[i].id = i;
    }
    std::sort(q + 1, q + m + 1);
    for (int i = 1, l = q[1].l, r = l - 1; i <= m; i++) {
        while (l > q[i].l) {
            l--;
            ans += cnt[l];
            cnt[L[l]]++;
            cnt[R[l]]++;
            if (L[l] >= l && L[l] <= r)
                ans++;
            if (R[l] >= l && R[l] <= r)
                ans++;
        }
        while (r < q[i].r) {
            r++;
            ans += cnt[r];
            cnt[L[r]]++;
            cnt[R[r]]++;
            if (L[r] >= l && L[r] <= r)
                ans++;
            if (R[r] >= l && R[r] <= r)
                ans++;
        }
        while (l < q[i].l) {
            cnt[L[l]]--;
            cnt[R[l]]--;
            if (L[l] >= l && L[l] <= r)
                ans--;
            if (R[l] >= l && R[l] <= r)
                ans--;
            ans -= cnt[l];
            l++;
        }
        while (r > q[i].r) {
            cnt[L[r]]--;
            cnt[R[r]]--;
            if (L[r] >= l && L[r] <= r)
                ans--;
            if (R[r] >= l && R[r] <= r)
                ans--;
            ans -= cnt[r];
            r--;
        }
        ret = ret + ans * q[i].id;
    }
    std::cout << ret << "\n";
    return 0;
}
