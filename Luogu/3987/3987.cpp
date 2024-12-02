#include <bits/stdc++.h>

#define int long long

constexpr int N = 5e5 + 7;

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
int a[N], t[N];
struct ques { int opt, x, y, z; } q[N];

std::vector<int> e[N];

void init(int u, int x) {
    for (int i = 1; i * i <= u; i++) {
        if (u % i == 0) {
            e[i].push_back(x);
            if (i * i != u)
                e[u / i].push_back(x);
        }
    }
}

int find1(int u, int x) {
    int l = 0, r = e[x].size() - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (e[x][mid] >= u) {
            ans = mid;
            r = mid - 1;
        } else l = mid + 1;
    }
    return ans;
}

int find2(int u, int x) {
    int l = 0, r = e[x].size() - 1, ans = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (e[x][mid] <= u) {
            ans = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    return ans;
}

struct SegTree {
    int tr[N << 2];

    #define ls(o) (o << 1)
    #define rs(o) (o << 1 | 1)

    void pushup(const int o) {
        tr[o] = tr[ls(o)] + tr[rs(o)];
    }

    void build(int o, int l, int r) {
        if (l == r) {
            tr[o] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(ls(o), l, mid);
        build(rs(o), mid + 1, r);
        pushup(o);
    }

    void update(int o, int l, int r, int p, int v) {
        if (l > p || r < p)
            return;
        if (l == p && r == p) {
            tr[o] /= v;
            return;
        }
        int mid = (l + r) >> 1;
        update(ls(o), l, mid, p, v);
        update(rs(o), mid + 1, r, p, v);
        pushup(o);
    }

    int query(int o, int l, int r, int ql, int qr) {
        if (l > qr || r < ql)
            return 0;
        if (ql <= l && r <= qr)
            return tr[o];
        int mid = (l + r) >> 1;
        int ret = query(ls(o), l, mid, ql, qr) + query(rs(o), mid + 1, r, ql, qr);
        return ret;
    }

    void divide(int l, int r, int v) {
        int _l = find1(l, v), _r = find2(r, v);
        if (_l == -1)
            return;
        for (int i = _l; i <= _r; i++) {
            // io.write(i, ' ');
            int u = e[v][i];
            if (a[u] % v == 0) {
                a[u] /= v;
                update(1, 1, n, u, v);
            } else if (t[v] >= 10000) {
                e[v].erase(e[v].begin() + i);
                i--, _r--;
            }
        }
    }
} seg;

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    io.read(n), io.read(m);
    for (int i = 1; i <= n; i++) {
        io.read(a[i]);
        init(a[i], i);
    }

    /* for (int i = 1; i <= n; i++) {
        for (auto x : e[i])
            std::cout << x << " ";
        std::cout << "\n";
    } */

    seg.build(1, 1, n);
    for (int i = 1; i <= m; i++) {
        io.read(q[i].opt);
        if (q[i].opt == 1) {
            io.read(q[i].x), io.read(q[i].y), io.read(q[i].z);
            ++t[q[i].z];
        } else { io.read(q[i].x), io.read(q[i].y); }
    }

    for (int i = 1; i <= m; i++) {
        if (q[i].opt == 1) {
            if (q[i].z == 1)
                continue;
            seg.divide(q[i].x, q[i].y, q[i].z);
            --t[q[i].z];
        } else io.write(seg.query(1, 1, n, q[i].x, q[i].y), '\n');
    }
    return 0;
}
