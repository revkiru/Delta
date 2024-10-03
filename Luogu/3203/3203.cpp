#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, q, bsiz;
int bid[N];
int jon[N], jot[N], stp[N];

struct node {
    int l, r;
} a[N];

void update(int l, int r) {
    for (int i = r; i >= l; i--) {
        if (i + jon[i] > a[bid[i]].r) {
            jot[i] = i + jon[i];
            stp[i] = 1;
        } else {
            jot[i] = jot[i + jon[i]];
            stp[i] = stp[i + jon[i]] + 1;
        }
    }
}

void init() {
    bsiz = std::sqrt(n);
    for (int i = 0; i < n; i++)
        bid[i] = i / bsiz;
    for (int i = 0; i <= bid[n - 1]; i++) {
        a[i].l = i * bsiz;
        a[i].r = (i + 1) * bsiz - 1;
    }
    a[bid[n - 1]].r = n - 1;
    update(0, n - 1);
}

int ask(int x) {
    int ret = 0;
    for (; x < n; x = jot[x]) {
        ret += stp[x];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &jon[i]);
    init();
    scanf("%d", &q);
    while (q--) {
        int op, x, y;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &x);
            printf("%d\n", ask(x));
        } else {
            scanf("%d %d", &x, &y);
            jon[x] = y;
            update(a[bid[x]].l, a[bid[x]].r);
        }
    }
    return 0;
}
