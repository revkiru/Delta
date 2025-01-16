#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e5 + 7;

int n, ans;
int cnt[N];

std::queue<int> q1, q2;

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

signed main() {
	io.read(n);
	for (int i = 1, x; i <= n; i++) {
		io.read(x);
		cnt[x]++;
	}

	for (int i = 1; i < N; i++) {
		for (; cnt[i]; cnt[i]--)
			q1.push(i);
	}

	for (int i = 1; i < n; i++) {
		int x = 0, y = 0;
		if ((!q1.empty() && q1.front() < q2.front()) || q2.empty()) {
			x = q1.front();
			q1.pop();
		} else {
			x = q2.front();
			q2.pop();
		}

		if ((!q1.empty() && q1.front() < q2.front()) || q2.empty()) {
			y = q1.front();
			q1.pop();
		} else {
			y = q2.front();
			q2.pop();
		}

		ans += (x + y);
		q2.push(x + y);
	}

	io.write(ans, '\n');
	return 0;
}
