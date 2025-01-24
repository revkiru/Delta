#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e6 + 7;

int n, m, ans;
int f[N][3];
bool vis[N];
std::vector<int> G[N << 1];

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

void dfs(int u) {
	vis[u] = 1;
	int fir = 0, sec = 0;
	for (auto v : G[u]) {
		if (vis[v]) continue;
		dfs(v);
		int dlt = f[v][0] - f[v][1];
		if (dlt > fir) { sec = fir; fir = dlt; }
		else if (dlt > sec) { sec = dlt; }
		f[u][0] += std::min(f[v][0] - 1, f[v][2]);
		f[u][1] += f[v][0];
	}
	f[u][0] += G[u].size() + 1;
	f[u][1] -= fir;
	f[u][2] = f[u][1] - sec;
}

int main() {
	io.read(n), io.read(m);
	ans = (n - 1) - m;
	for (int i = 1, u, v; i <= m; i++) {
		io.read(u), io.read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	for (int i = 1; i <= n; i++) {
		if (!vis[i]) {
			dfs(i);
			ans += std::min(f[i][0], f[i][2]);
		}
	}
	io.write(ans, '\n');
	return 0;
}
