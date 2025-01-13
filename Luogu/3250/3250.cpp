#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int M = 2e5 + 7;

int n, m, dfx;
int dep[N], fa[N], siz[N], son[N], dfn[N], top[N];
std::pair<int, int> cov[N];

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

struct TwiProirityQueue {
	std::priority_queue<int> q1, q2;

	int top() {
		while (!q1.empty() && !q2.empty() && q1.top() == q2.top()) {
			q1.pop();
			q2.pop();
		}
		return q1.empty() ? -1 : q1.top();
	}

	void insert(int val) {
		q1.push(val);
	}

	void erase(int val) {
		q2.push(val);
	}
};

struct SegTree {
	TwiProirityQueue tr[N << 2];

	#define ls(o) (o << 1)
	#define rs(o) (o << 1 | 1)

	void update(int o, int l, int r, int ql, int qr, int v, int t) {
		if (ql <= l && r <= qr)
			return t ? tr[o].insert(v) : tr[o].erase(v);
		int mid = (l + r) >> 1;
		if (ql <= mid)
			update(ls(o), l, mid, ql, qr, v, t);
		if (qr > mid)
			update(rs(o), mid + 1, r, ql, qr, v, t);
	}

	int query(int o, int k, int l, int r) {
		if (l == r)
			return tr[o].top();
		int mid = (l + r) >> 1, ret = tr[o].top();
		if (k <= mid)
			return std::max(ret, query(ls(o), k, l, mid));
		else
			return std::max(ret, query(rs(o), k, mid + 1, r));
	}
} seg;

struct task {
	int a, b, v;
} tsk[M];

std::vector<int> G[M];

void dfs1(int u, int pa) {
	dep[u] = dep[fa[u] = pa] + 1;
	siz[u] = 1;

	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v != pa) {
			dfs1(v, u);
			siz[u] += siz[v];
			if (siz[son[u]] < siz[v])
				son[u] = v;
		}
	}
}

void dfs2(int u, int tp) {
	dfn[u] = ++dfx;
	top[u] = tp;
	if (son[u])
		dfs2(son[u], tp);
	for (size_t i = 0; i < G[u].size(); i++) {
		int v = G[u][i];
		if (v != fa[u] && v != son[u])
			dfs2(v, v);
	}
}

void pou(int x, int y, int val, int t) {
	int cot = 0;
	while (top[x] != top[y]) {
		if (dep[top[y]] > dep[top[x]])
			std::swap(x, y);
		cov[++cot] = {dfn[top[x]], dfn[x]};
		x = fa[top[x]];
	}
	if (dep[y] > dep[x])
		std::swap(x, y);
	cov[++cot] = {dfn[y], dfn[x]};
	std::sort(cov + 1, cov + cot + 1);
	for (int i = 1, l = 0; i <= cot; l = cov[i].second, i++) {
		if (l + 1 != cov[i].first)
			seg.update(1, 1, n, l + 1, cov[i].first - 1, val, t);
	}
	if (cov[cot].second != n)
		seg.update(1, 1, n, cov[cot].second + 1, n, val, t);
}

int main() {
	io.read(n), io.read(m);
	for (int i = 1, u, v; i < n; i++) {
		io.read(u), io.read(v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs1(1, 0);
	dfs2(1, 1);
	for (int i = 1, opt, a, b, v; i <= m; i++) {
		io.read(opt);
		if (opt == 0) {
			io.read(a), io.read(b), io.read(v);
			tsk[i] = {a, b, v};
			pou(a, b, v, 1);
		}
		if (opt == 1) {
			io.read(a);
			pou(tsk[a].a, tsk[a].b, tsk[a].v, 0);
		}
		if (opt == 2) {
			io.read(a);
			io.write(seg.query(1, dfn[a], 1, n), '\n');
		}
	}
	return 0;
}
