#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int inf = 1e9;

int n;
i64 ans, a[N], mn[N];

void solve(int l, int r) {
    if (l == r)
        return;
    int mid = (l + r) >> 1, p = 0;
    i64 mnn, mxn;

    mxn = mnn = a[mid], p = mid;
    for (int i = mid; i >= l; i--) {
        mnn = std::min(mnn, a[i]), mxn = std::max(mxn, a[i]);
        while (a[p + 1] < mxn && a[p + 1] >= mnn && p < r)
            p++;
        ans += (mxn - mnn) * (p - mid);
    }

    mnn = mxn = a[mid + 1], p = mid + 1;
    for (int i = mid + 1; i <= r; i++) {
        mnn = std::min(mnn, a[i]), mxn = std::max(mxn, a[i]);
        while (a[p - 1] <= mxn && a[p - 1] > mnn && p > l)
            p--;
        ans += (mxn - mnn) * (mid - p + 1);
    }

    int _l = mid + 1, _r = mid;
    i64 res = 0;
    mxn = mnn = a[mid], mn[mid] = inf;
    for (int i = mid; i >= l; i--) {
        mnn = std::min(mnn, a[i]), mxn = std::max(mxn, a[i]);
        while (a[_r + 1] < mxn && _r < r) {
            _r++;
            mn[_r] = std::min(mn[_r - 1], a[_r]);
            res += mn[_r];
        }
        while (_l <= _r && mnn <= mn[_l]) {
            res -= mn[_l];
            _l++;
        }
        ans += mxn * (_r - _l + 1) - res;
    }

    mnn = mxn = a[mid + 1], mn[mid + 1] = inf;
    _l = mid + 1, _r = mid, res = 0;
    for (int i = mid + 1; i <= r; i++) {
        mnn = std::min(mnn, a[i]), mxn = std::max(mxn, a[i]);
        while (a[_l - 1] <= mxn && _l > l) {
            _l--;
            mn[_l] = std::min(mn[_l + 1], a[_l]);
            res += mn[_l];
        }
        while (_r >= _l && mn[_r] > mnn) {
            res -= mn[_r];
            _r--;
        }
        ans += mxn * (_r - _l + 1) - res;
    }
    solve(l, mid);
    solve(mid + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++)
        std::cin >> a[i];
    solve(1, n);
    std::cout << ans << "\n";
    return 0;
}
