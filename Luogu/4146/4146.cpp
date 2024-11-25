#include <bits/stdc++.h>

using namespace std;

constexpr int N = 1e5 + 7;

int n, m, root, cnt;

struct node
{
    int l, r, val, max, rd, siz, rev, add;
} tr[N];

// #define DEBUG 1  // 调试开关
struct IO
{
#define MAXsiz (1 << 20)
#define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXsiz], *p1, *p2;
    char pbuf[MAXsiz], *pp;
#if DEBUG
#else
    IO() : p1(buf), p2(buf), pp(pbuf) {}

    ~IO() { fwrite(pbuf, 1, pp - pbuf, stdout); }
#endif
    char gc()
    {
#if DEBUG // 调试，可显示字符
        return getchar();
#endif
        if (p1 == p2)
            p2 = (p1 = buf) + fread(buf, 1, MAXsiz, stdin);
        return p1 == p2 ? ' ' : *p1++;
    }

    bool blank(char ch)
    {
        return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
    }

    template <class T>
    void read(T &x)
    {
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

    void read(char *s)
    {
        char ch = gc();
        for (; blank(ch); ch = gc())
            ;
        for (; !blank(ch); ch = gc())
            *s++ = ch;
        *s = 0;
    }

    void read(char &c)
    {
        for (c = gc(); blank(c); c = gc())
            ;
    }

    void push(const char &c)
    {
#if DEBUG // 调试，可显示字符
        putchar(c);
#else
        if (pp - pbuf == MAXsiz)
            fwrite(pbuf, 1, MAXsiz, stdout), pp = pbuf;
        *pp++ = c;
#endif
    }

    template <class T>
    void write(T x)
    {
        if (x < 0)
            x = -x, push('-'); // 负数输出
        static T sta[35];
        T top = 0;
        do
        {
            sta[top++] = x % 10, x /= 10;
        } while (x);
        while (top)
            push(sta[--top] + '0');
    }

    template <class T>
    void write(T x, char lastChar)
    {
        write(x), push(lastChar);
    }
} io;

int newnode(int val)
{
    tr[++cnt].val = val, tr[cnt].rd = rand() * rand(), tr[cnt].siz = 1;
    return cnt;
}
void update(int now)
{
    tr[0].add = 0;
    tr[0].val = 0;
    tr[0].max = -2e9;
    tr[now].siz = tr[tr[now].l].siz + tr[tr[now].r].siz + 1;
    tr[now].max = max(tr[now].val, max(tr[tr[now].l].max, tr[tr[now].r].max));
}
void pushdown(int now)
{
    tr[0].add = 0;
    tr[0].val = 0;
    tr[0].max = -2e9;
    if (tr[now].rev)
    {
        swap(tr[now].l, tr[now].r);
        tr[tr[now].l].rev ^= 1, tr[tr[now].r].rev ^= 1;
        tr[now].rev = 0;
    }
    if (tr[now].add)
    {
        tr[tr[now].l].add += tr[now].add, tr[tr[now].r].add += tr[now].add;
        tr[tr[now].l].val += tr[now].add, tr[tr[now].r].val += tr[now].add;
        tr[tr[now].l].max += tr[now].add, tr[tr[now].r].max += tr[now].add;
        tr[now].add = 0;
    }
}
void split(int now, int w, int &u, int &v)
{
    if (!now) {
        u = v = 0;
        return;
    }
    pushdown(now);
    if (tr[tr[now].l].siz < w)
        u = now, split(tr[now].r, w - tr[tr[now].l].siz - 1, tr[now].r, v);
    else
        v = now, split(tr[now].l, w, u, tr[now].l);
    update(now);
}
int merge(int u, int v)
{
    if (!u || !v)
        return u + v;
    if (tr[u].rd < tr[v].rd)
    {
        pushdown(u);
        tr[u].r = merge(tr[u].r, v);
        update(u);
        return u;
    }
    else
    {
        pushdown(v);
        tr[v].l = merge(u, tr[v].l);
        update(v);
        return v;
    }
}
int main()
{
    srand(time(nullptr));
    io.read(n), io.read(m);
    for (int i = 1; i <= n; i++)
    {
        root = merge(root, newnode(0));
        // std::cout << root << "\n";
    }
    while (m--)
    {
        int opt, l, r, v, x, y, z;
        io.read(opt);
        if (opt == 1)
        {
            io.read(l), io.read(r), io.read(v);
            split(root, r, x, y);
            split(x, l - 1, x, z);
            tr[z].add += v;
            tr[z].val += v;
            tr[z].max += v;
            root = merge(merge(x, z), y);
            // std::cout << root << "\n";
        }
        if (opt == 2)
        {
            io.read(l), io.read(r);
            split(root, r, x, y);
            split(x, l - 1, x, z);
            tr[z].rev ^= 1;
            root = merge(merge(x, z), y);
        }
        if (opt == 3)
        {
        	io.read(l), io.read(r);
            split(root, r, x, y);
            split(x, l - 1, x, z);
            io.write(tr[z].max, '\n');
            root = merge(merge(x, z), y);
        }
    }
    return 0;
}