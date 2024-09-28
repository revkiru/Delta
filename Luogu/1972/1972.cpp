#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar_unlocked();
	for (; !isdigit(ch); ch = getchar_unlocked()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar_unlocked()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar_unlocked('-'); }
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + '0');
}

int n, m, unt, ret, t0t;
int a[N], c[N], ans[N], fro[N], h[N];

struct ques {
    int l, r, id;

    bool operator < (const ques &x) const {
        if (l / unt != x.l / unt) return l < x.l;
        if ((l / unt) & 1) return r < x.r;
        return r > x.r;
    }
} q[N];

void add(int i) {
    if (!c[i]) ret++;
    c[i]++;
}

void del(int i) {
    c[i]--;
    if (!c[i]) ret--;
}

int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<int>();
        if (!fro[a[i]]) {
            fro[a[i]] = ++t0t;
        }
        a[i] = fro[a[i]];
    }
    m = read<int>();
    for (int i = 1; i <= m; i++) {
        q[i].l = read<int>(), q[i].r = read<int>();
        q[i].id = i;
    }

    unt = n / std::sqrt(m);
    std::sort(q + 1, q + m + 1);
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        // while (l > q[i].l) add(a[--l]);
        // while (r < q[i].r) add(a[++r]);
        // while (l < q[i].l) del(a[l++]);
        // while (r > q[i].r) del(a[r--]);
        while (l > q[i].l) ret += !(bool) h[a[--l]]++;
        while (r < q[i].r) ret += !(bool) h[a[++r]]++;
        while (l < q[i].l) ret -= !(bool) --h[a[l++]];
        while (r > q[i].r) ret -= !(bool) --h[a[r--]];
        ans[q[i].id] = ret;
    }

    for (int i = 1; i <= m; i++) {
        write<int>(ans[i]);
        puts("");
    }
    return 0;
}
