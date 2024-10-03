#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 4e4 + 7;

int n, m, tot, bsiz;
int a[N], b[N], t[N];
int s[207][N], f[207][N];

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int bid(int i) { return (i - 1) / bsiz + 1; }

int main() {
	n = read<int>(), m = read<int>();
    bsiz = std::sqrt(n);
    for (int i = 1; i <= n; i++) {
		a[i] = read<int>();
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    int t0t = std::unique(b + 1, b + n + 1) - b - 1;
    tot = (n - 1) / bsiz + 1;
    for (int i = 1; i <= n; i++)
        a[i] = std::lower_bound(b + 1, b + t0t + 1, a[i]) - b;
    for (int i = 1; i <= tot; i++) {
        for (int j = bsiz * (i - 1) + 1; j <= std::min(bsiz * i, n); j++)
            s[i][a[j]]++;
        for (int j = 1; j <= t0t; j++)
            s[i][j] += s[i - 1][j];
    }
    for (int i = 1; i <= tot; i++) {
        for (int j = i; j <= tot; j++) {
            int mx = f[i][j - 1];
            for (int k = bsiz * (j - 1) + 1; k <= std::min(bsiz * j, n); k++)
                if ((s[j][a[k]] - s[i - 1][a[k]] > s[j][mx] - s[i - 1][mx]) || (s[j][a[k]] - s[i - 1][a[k]] == s[j][mx] - s[i - 1][mx] && a[k] < mx))
                    mx = a[k];
            f[i][j] = mx;
        }
    }
    // printf("%d\n%d\n", s[1][n], f[1][n]);
    int x = 0;
    while (m--) {
        int l = (read<int>() + x - 1) % n + 1, r = (read<int>() + x - 1) % n + 1;
        if (l > r)
            std::swap(l, r);
        // printf("%d %d\n", l, r);
        int bl = bid(l), br = bid(r), mx = 0;
        if (br - bl <= 1) {
            for (int i = l; i <= r; i++)
                t[a[i]]++;
            for (int i = l; i <= r; i++)
                if (t[a[i]] > t[mx] || (t[a[i]] == t[mx] && a[i] < mx))
                    mx = a[i];
            for (int i = l; i <= r; i++)
                t[a[i]] = 0;
        } else {
            for (int i = l; i <= bsiz * bl; i++)
                t[a[i]]++;
            for (int i = bsiz * (br - 1) + 1; i <= r; i++)
                t[a[i]]++;
            mx = f[bl + 1][br - 1];
            for (int i = l; i <= bsiz * bl; i++) {
                int pre = t[mx] + s[br - 1][mx] - s[bl][mx];
                int now = t[a[i]] + s[br - 1][a[i]] - s[bl][a[i]];
                if (now > pre || (now == pre && mx > a[i]))
                    mx = a[i];
            }
            for (int i = bsiz * (br - 1) + 1; i <= r; i++) {
                int pre = t[mx] + s[br - 1][mx] - s[bl][mx];
                int now = t[a[i]] + s[br - 1][a[i]] - s[bl][a[i]];
                if (now > pre || (now == pre && mx > a[i]))
                    mx = a[i];
            }
            for (int i = l; i <= bsiz * bl; i++)
                t[a[i]] = 0;
            for (int i = bsiz * (br - 1) + 1; i <= r; i++)
                t[a[i]] = 0;
        }
        x = b[mx];
        write<int>(x);
        puts("");
    }
    return 0;
}
