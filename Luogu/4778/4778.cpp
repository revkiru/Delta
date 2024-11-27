#include <bits/stdc++.h>

#define int __int128

constexpr int N = 1e5 + 7;
constexpr int P = 1e9 + 9;

int n;
int p[N], v[N];
int fac[N], ifc[N];

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

template <typename T>
T expow(T a, T b) {
	T res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a % P;
		a = a * a % P;
	}
	return res;
}

void init() {
	fac[0] = 1;
	for (int i = 1; i <= (int) 1e5; i++)
		fac[i] = fac[i - 1] * i % P;
	ifc[(int) 1e5] = expow(fac[(int) 1e5], P - 2);
	for (int i = (int) 1e5 - 1; ~i; i--)
		ifc[i] = ifc[i + 1] * (i + 1) % P;
}

int calc(int k) {
	int cot = 1;
	v[k] = 1;
	for (int i = p[k]; i != k; i = p[i]) { cot++; v[i] = 1; } 
	return (cot == 1 ? 1 : expow(cot, cot - 2)) * ifc[cot - 1] % P;
}

void solve() {
	io.read(n);
	for (int i = 1; i <= n; i++) {
		io.read(p[i]);
		v[i] = 0;
	}

	int cnt = 0, ans = 1;
	for (int i = 1; i <= n; i++) {
		if (v[i]) { continue; }
		ans = ans * calc(i) % P;
		cnt++;
	}
	ans = ans * fac[n - cnt] % P;
	io.write(ans, '\n');
}

signed main() {
	init();
	int t;
	io.read(t);
	while (t--) {
		solve();
	}
	return 0;
}
