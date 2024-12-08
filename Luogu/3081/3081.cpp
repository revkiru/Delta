#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n;

struct line {
    int idx;
    int x0, y0, x1, y1;

    bool operator < (const line &s) const {
        if (x1 < s.x1)
            return 1ll * (s.x1 - x1) * (s.y1 - s.y0) < 1ll * (s.x1 - s.x0) * (s.y1 - y1);
        else
            return 1ll * (x1 - s.x1) * (y1 - y0) > 1ll * (x1 - x0) * (y1 - s.y1);
    }
} a[N];

struct point {
    int x, y, l;

    bool operator < (const point &s) const {
        if (x == s.x)
            return y < s.y;
        return x < s.x;
    }
} b[N];

std::set<line> st;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i].x0 >> a[i].y0 >> a[i].x1 >> a[i].y1;
        a[i].idx = i;
        b[i * 2 - 1] = {a[i].x0, a[i].y0, i};
        b[i * 2] = {a[i].x1, a[i].y1, i};
    }

    int cur = 1, ans = 1;
    st.insert(a[1]);
    std::sort(b + 1, b + 2 * n + 1);
    for (int i = 2; i <= n * 2; i++) {
        point u = b[i];
        // std::cout << u.x << " " << u.y << " " << u.l << "---\n";
        // std::cout << st.size() << "---\n";
        if (b[i].x == a[b[i].l].x0)     // 开始
            st.insert(a[b[i].l]);
        else {
            if (u.l == cur) {   // 结束
                auto it = st.find(a[b[i].l]);
                if (it == st.begin())
                    break;
                auto _it = it;
                _it--;
                st.erase(it);
                cur = _it -> idx;
                ans++;
            } else {
                st.erase(a[b[i].l]);
            }
        }
    }
    std::cout << ans << "\n";
    return 0;
}
