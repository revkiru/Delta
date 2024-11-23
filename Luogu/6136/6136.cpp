#include <bits/stdc++.h>

#define int long long

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

constexpr int N = 1e6 + 7;

std::random_device rdv;
std::mt19937 myrand(rdv());

int n, m;

struct node {
	int rd, siz, val, ls, rs;
};

struct FHQ_Treap {
	int tim, rt, l, r, mid, sum;
	node tr[N << 1];

	int newnode(int x) {
		++tim;
		tr[tim].val = x; tr[tim].siz = 1; tr[tim].rd = myrand();
		return tim;
	}

	void pushup(int o) {
		tr[o].siz = tr[tr[o].ls].siz + tr[tr[o].rs].siz + 1;
	}

	void split(int o, int k, int &x, int &y) {
		if (o == 0) { x = y = 0; return; }
		if (tr[o].val <= k) {
			x = o;
			split(tr[o].rs, k, tr[o].rs, y);
		} else {
			y = o;
			split(tr[o].ls, k, x, tr[o].ls);
		}
		pushup(o);
	}

	int merge(int x, int y) {
		if (x == 0 || y == 0) { return x + y; }
		if (tr[x].rd < tr[y].rd) {
			tr[x].rs = merge(tr[x].rs, y);
			pushup(x);
			return x;
		} else {
			tr[y].ls = merge(x, tr[y].ls);
			pushup(y);
			return y;
		}
	}

	void insert(int x) {
		split(rt, x, l, r);
		rt = merge(merge(l, newnode(x)), r);
	}

	void remove(int x) {
		split(rt, x, l, r);
		split(l, x - 1, l, mid);
		mid = merge(tr[mid].ls, tr[mid].rs);
		rt = merge(merge(l, mid), r);
	}

	int kth(int o, int k) {
		while (1) {
			if (k <= tr[tr[o].ls].siz) {
				o = tr[o].ls;
			} else {
				if (k == tr[tr[o].ls].siz + 1) {
					return o;
				} else {
					k -= tr[tr[o].ls].siz + 1;
					o = tr[o].rs;
				}
			}
		}
	}

	int rank(int k) {
		split(rt, k - 1, l, r);
		int rk = tr[l].siz + 1;
		rt = merge(l, r);
		return rk;
	}

	int query_pre(int k) {
		split(rt, k - 1, l, r);
		int ret = tr[kth(l, tr[l].siz)].val;
		rt = merge(l, r);
		return ret;
	}

	int query_suf(int k) {
		split(rt, k, l, r);
		int ret = tr[kth(r, 1)].val;
		rt = merge(l, r);
		return ret;
	}
} trp;

int lst, ans;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("6136_ex/P6136_1.in", "r", stdin);

	io.read(n), io.read(m);
	for (int i = 1, a; i <= n; i++) {
		io.read(a);
		trp.insert(a);
	}
	for (int i = 1, opt, x; i <= m; i++) {
		io.read(opt), io.read(x);
		x ^= lst;
		// io.write(x, '-');
		if (opt == 1) { trp.insert(x); };
		if (opt == 2) { trp.remove(x); };
		if (opt == 3) { lst = trp.rank(x); ans ^= lst; }
		if (opt == 4) { lst = trp.tr[trp.kth(trp.rt, x)].val; ans ^= lst; }
		if (opt == 5) { lst = trp.query_pre(x); ans ^= lst; }
		if (opt == 6) { lst = trp.query_suf(x); ans ^= lst; }
	}
	// io.write(lst, '\n');
	io.write(ans, '\n');
	return 0;
}
