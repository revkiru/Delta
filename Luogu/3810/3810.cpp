#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int K = 2e5 + 7;

int n, k, m, t;
int res[N];

struct node {
    int a, b, c, cnt, ret;
    
    bool operator != (node other) const {
        if (a != other.a) return 1;
        if (b != other.b) return 1;
        if (c != other.c) return 1;
        return 0;
    }
} e[N], ue[N];

struct Fenwick {
    int tr[K];

    int lowbit(int x) { return x & -x; }

    void add(int i, int x) {
        for (; i <= k; i += lowbit(i)) {
            tr[i] += x;
        }
    }

    int query(int i) {
        int ret = 0;
        for (; i; i -= lowbit(i)) {
            ret += tr[i];
        }
        return ret;
    }
} bit;

bool cmpA(const node &x, const node &y) {
    if (x.a != y.a) return x.a < y.a;
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

bool cmpB(const node &x, const node &y) {
    if (x.b != y.b) return x.b < y.b;
    return x.c < y.c;
}

void CDQ(int l, int r) {
    if (l == r) return;
    int mid = (l + r) / 2;
    CDQ(l, mid);
    CDQ(mid + 1, r);
    std::sort(ue + l, ue + mid + 1, cmpB);
    std::sort(ue + mid + 1, ue + r + 1, cmpB);
    int i = l, j = mid + 1;
    while (j <= r) {
        while (i <= mid && ue[i].b <= ue[j].b) {
            bit.add(ue[i].c, ue[i].cnt);
            i++;
        }
        ue[j].ret += bit.query(ue[j].c);
        j++;
    }
    for (int k = l; k < i; k++)
        bit.add(ue[k].c, -ue[k].cnt);
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d %d %d", &e[i].a, &e[i].b, &e[i].c);
    std::sort(e + 1, e + n + 1, cmpA);
    for (int i = 1; i <= n; i++) {
        t++;
        if (e[i] != e[i + 1]) {
            m++;
            ue[m] = e[i];
            ue[m].cnt = t;
            t = 0;
        }
    }
    CDQ(1, m);
    for (int i = 1; i <= m; i++)
        res[ue[i].ret + ue[i].cnt - 1] += ue[i].cnt;
    for (int i = 0; i < n; i++)
        printf("%d\n", res[i]);
    return 0;
}
