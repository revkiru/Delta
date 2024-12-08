#include <bits/stdc++.h>
#include <ext/rope>

using i64 = long long;

constexpr int N = 2e5 + 7;

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

int n, m;
int ini[N], rd[N];
__gnu_cxx::rope<int> fa[N];

int find(__gnu_cxx::rope<int> &fa, int x) {
    return (x == fa[x]) ? x : find(fa, fa[x]);
}

void merge(__gnu_cxx::rope<int> &fa, int x, int y) {
    x = find(fa, x), y = find(fa, y);
    if (x == y)
        return;
    if (rd[x] > rd[y])
        fa.replace(y, x);
    else
        fa.replace(x, y);
}

int main() {
    io.read(n), io.read(m);

    ini[0] = 1;
    for (int i = 1; i <= n; i++) {
        rd[i] = myrand();
        ini[i] = i;
    }
    fa[0] = __gnu_cxx::rope<int>(ini);

    for (int i = 1, opt, x, y; i <= m; i++) {
        io.read(opt);
        switch (opt) {
            case 1:
                fa[i] = fa[i - 1];
                io.read(x), io.read(y);
                merge(fa[i], x, y);
                break;
            case 2:
                io.read(x);
                fa[i] = fa[x];
                break;
            case 3:
                fa[i] = fa[i - 1];
                io.read(x), io.read(y);
                io.write((find(fa[i], x) == find(fa[i], y) ? 1 : 0), '\n');
            default:
                break;
        }
    }
    return 0;
}
