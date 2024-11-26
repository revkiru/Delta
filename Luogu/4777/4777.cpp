#include <bits/stdc++.h>

#define int __int128

constexpr int N = 1e5 + 7;

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

int n, x, y, d;
int a, b, A, B;

template <typename T>
void exgcd(T a, T b, T &x, T &y) {
	if (b == 0) { d = a; x = 1; y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

template <typename T>
T mylcm(T a, T b) { return a / std::__gcd(a, b) * b; }

void merge() {
	exgcd(a, A, x, y);
	int c = B - b;
	// std::cerr << x << ", " << y << ", " << d << "\n";
	if (c % d) { std::cout << "-1\n"; exit(0); }
	x = x * c / d % (A / d);
	if (x < 0) { x += A / d; }
	int mod = mylcm(a, A);
	b = (a * x + b) % mod;
	if (b < 0) { b += mod; }
	a = mod;
}

signed main() {
	io.read(n);
	io.read(a), io.read(b);
	for (int i = 2; i <= n; i++) {
		io.read(A), io.read(B);
		merge();
	}
	io.write((b % a), '\n');
	return 0;
}
