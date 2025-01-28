#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int M = 2e5 + 7;

int n, _s, _t, rt, ans = 3;
int cnt[M];

std::bitset<N> st;
std::queue<int> q;
std::map<int, std::set<int>> mp;

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

struct edge {
	int etot, head[N], ind[N], nxt[M << 1], to[M << 1];
	bool v[N];

	void init() {
		etot = 0;
		memset(head, -1, sizeof(head));
	}

	void insert(int x, int y) {
		++ind[y];
		to[++etot] = y;
		nxt[etot] = head[x];
		head[x] = etot;
	}
} g1, g2, gf;

struct element {
	int ind, c;

	bool operator < (const element &rhs) const { return c > rhs.c; }
};
std::set<element> s;

void insert(int d, int od) {
	auto it = s.find({ d, cnt[d] });
	if (it != s.end()) s.erase(it);
	cnt[d] += od;
	s.insert({ d, cnt[d] });
}

int main() {
	g1.init(); g2.init(); gf.init();

	io.read(n);
	io.read(_s);
	for (int i = 1, u, v; i <= _s; ++i) {
		io.read(u), io.read(v);
		g1.insert(u, v);
		g1.insert(v, u);
	}

	io.read(_t);
	for (int i = 1, u, v; i <= _t; ++i) {
		io.read(u), io.read(v);
		g2.insert(u, v); 
		g2.insert(v, u);
	}

	io.write(ans, '\n');
	for (int i = 1; i <= n; ++i)
		if (g2.ind[i] == 1)
			st.set(i, 1);
	for (int i = 1; i <= n; ++i)
		if (st[i]) {
			rt = i;
			break;
		}

	int lu = 0, lv = 0;
	for (int i = 1; i <= n; ++i) {
		int d = g1.ind[i];
		if (mp.find(d) == mp.end()) mp[d] = { i };
		else mp[d].insert(i);
		insert(d, 1);
	}
	for (int i = 1; i < n; ++i) {
		auto it1 = s.begin();
		int d = it1 -> ind;
		auto it2 = mp[d].begin();
		lu = *it2;
		++it2;
		lv = *it2;

		gf.insert(lu, lv);
		gf.insert(lv, lu);
		if (lv == rt)
			std::swap(lu, lv);
		g1.v[lu] = true;
		mp[d].erase(lu);
		insert(g1.ind[lu], -1);

		io.write(lu, ' ');
		io.write(lv, '\n');
		for (int i = g1.head[lu]; ~i; i = g1.nxt[i]) {
			int y = g1.to[i];
			if (g1.v[y]) continue;
			mp[g1.ind[y]].erase(y);
			insert(g1.ind[y], -1);

			--g1.ind[y];
			if (mp.find(g1.ind[y]) == mp.end()) mp[g1.ind[y]] = { y };
			else mp[g1.ind[y]].insert(y);
			insert(g1.ind[y], 1);
		}
	}

	gf.v[rt] = 1;
	for (int i = 1; i <= n; ++i)
		if (gf.ind[i] == 1 && !gf.v[i])
			q.push(i);
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		if (gf.v[v]) continue;
		gf.v[v] = 1;
		io.write(v, ' ');
		io.write(rt, '\n');
		for (int i = gf.head[v]; ~i; i = gf.nxt[i]) {
			int y = gf.to[i];
			if (gf.v[y]) continue;
			if (--gf.ind[y] == 1) q.push(y);
			break;
		}
	}

	for (int i = 1; i <= n; ++i)
		if (g2.ind[i] == 1 && i != rt)
			q.push(i);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		if (g2.v[v]) continue;
		g2.v[v] = 1;
		for (int i = g2.head[v]; ~i; i = g2.nxt[i]) {
			int y = g2.to[i];
			if (g2.v[y]) continue;
			io.write(v, ' ');
			io.write(y, '\n');
			if (--g2.ind[y] == 1) q.push(y);
			break;
		}
	}
	return 0;
}
