#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;
constexpr int M = 40;

std::random_device rdv;
std::mt19937 myrand(rdv());

// #define DEBUG 1  // 调试开关
struct IO {
#define MAXSIZE (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
#if DEBUG
#else
    IO() : p1(buf), p2(buf), pp(pbuf) {}

    ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
    char gc() {
#if DEBUG // 调试，可显示字符
        return getchar();
#endif
        if (p1 == p2)
            p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin);
        return p1 == p2 ? ' ' : *p1++;
    }

    bool blank(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    template <class T>
    void read(T &x) {
        double tmp = 1;
        bool sign = false;
        x = 0;
        char ch = gc();
        for (; !isdigit(ch); ch = gc())
            if (ch == '-')
                sign = 1;
        for (; isdigit(ch); ch = gc())
            x = x * 10 + (ch - '0');
        if (ch == '.')
            for (ch = gc(); isdigit(ch); ch = gc())
                tmp /= 10.0, x += tmp * (ch - '0');
        if (sign)
            x = -x;
    }

    void read(char *s) {
        char ch = gc();
        for (; blank(ch); ch = gc())
            ;
        for (; !blank(ch); ch = gc())
            *s++ = ch;
        *s = 0;
    }

    void read(char &c) {
        for (c = gc(); blank(c); c = gc())
            ;
    }

    void push(const char &c) {
#if DEBUG // 调试，可显示字符
        putchar(c);
#else
        if (pp - pbuf == MAXSIZE)
            fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
#endif
    }

    template <class T>
    void write(T x) {
        if (x < 0)
            x = -x, push('-'); // 负数输出
        static T sta[35];
        T top = 0;
        do {
            sta[top++] = x % 10, x /= 10;
        } while (x);
        while (top)
            push(sta[--top] + '0');
    }

    template <class T>
    void write(T x, char lastChar) {
        write(x), push(lastChar);
    }
} io;

int n, m, unit;
int a[N], cnt[N], ans[N];

struct ques {
	int id, pos, l, r;

	bool operator < (const ques &x) const {
		if (pos != x.pos) return pos < x.pos;
		if (pos & 1) return r > x.r;
		return r < x.r;
	}
} qs[N];

#define add(x) ++cnt[a[x]]
#define del(x) --cnt[a[x]]

int main() {
	io.read(n), io.read(m);
	unit = std::ceil(n / std::sqrt(m));
	for (int i = 1; i <= n; i++)
		io.read(a[i]);
	for (int i = 1; i <= m; i++) {
		io.read(qs[i].l);
		io.read(qs[i].r);
		qs[i].id = i;
		qs[i].pos = (qs[i].l  - 1) / unit + 1;
	}
	std::sort(qs + 1, qs + m + 1);
	for (int i = 1, l = 1, r = 0; i <= m; i++) {
		int lim = (qs[i].r - qs[i].l + 1) / 2;
		while (l > qs[i].l) add(--l);
		while (r < qs[i].r) add(++r);
		while (l < qs[i].l) del(l++);
		while (r > qs[i].r) del(r--);
		for (int _t = 1; _t <= M; _t++) {
			int rd = myrand() % (qs[i].r - qs[i].l + 1) + qs[i].l;
			if (cnt[a[rd]] > lim) {
				ans[qs[i].id] = a[rd];
				break;
			}
		}
	}
	for (int i = 1; i <= m; i++)
		io.write(ans[i], '\n');
	return 0;
}
