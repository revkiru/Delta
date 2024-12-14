#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m;
i64 ans;
int rv[N];

struct node {
    int val, del, ans;
} a[N];

struct Fenwick {
    int tr[N << 1];

    int lowbit(int x) { return x & -x; }

    void add(int i, int x) {
        for (; i <= n + 1; i += lowbit(i))
            tr[i] += x;
    }

    int query(int i) {
        int res = 0;
        for (; i; i -= lowbit(i))
            res += tr[i];
        return res;
    }
} bit;

bool cmp1(const node &a, const node &b) {
    return a.val < b.val;
}

bool cmp2(const node &a, const node &b) {
    return a.del < b.del;
}

void CDQ(int l, int r) {
    if (r - l == 1) return;
    int mid = (l + r) / 2;
    CDQ(l, mid);
    CDQ(mid, r);

    int i = l + 1, j = mid + 1;
    while (i <= mid) {
        while (a[i].val > a[j].val && j <= r) {
            bit.add(a[j].del, 1);
            j++;
        }
        a[i].ans += bit.query(m + 1) - bit.query(a[i].del);
        i++;
    }
    i = l + 1, j = mid + 1;
    while (i <= mid) {
        while (a[i].val > a[j].val && j <= r) {
            bit.add(a[j].del, -1);
            j++;
        }
        i++;
    }

    i = mid, j = r;
    while (j > mid) {
        while (a[j].val < a[i].val && i > l) {
            bit.add(a[i].del, 1);
            i--;
        }
        a[j].ans += bit.query(m + 1) - bit.query(a[j].del);
        j--;
    }
    i = mid, j = r;
    while (j > mid) {
        while (a[j].val < a[i].val && i > l) {
            bit.add(a[i].del, -1);
            i--;
        }
        j--;
    }
    std::sort(a + l + 1, a + r + 1, cmp1);
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i].val);
        rv[a[i].val] = i;
    }
    for (int i = 1, x; i <= m; i++) {
        scanf("%d", &x);
        a[rv[x]].del = i;
    }
    for (int i = 1; i <= n; i++) {
        if (!a[i].del)
            a[i].del = m + 1;
    }
    for (int i = 1; i <= n; i++) {
        ans += bit.query(n + 1) - bit.query(a[i].val);
        bit.add(a[i].val, 1);
    }
    for (int i = 1; i <= n; i++)
        bit.add(a[i].val, -1);
    CDQ(0, n);
    std::sort(a + 1, a + n + 1, cmp2);
    for (int i = 1; i <= m; i++) {
        printf("%lld\n", ans);
        ans -= a[i].ans;
    }
    return 0;
}
