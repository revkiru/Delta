#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

constexpr int N = 4e7 + 7;
constexpr int M = 1e5 + 7;
constexpr int P = 1 << 30;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}

int n, m, type;
int head, tail;
int b[N], mtq[N], f[N];
int p[M], l[M], r[M];
i64 s[N];

i128 v(const int idx) {
	return ((i128) s[idx] << 1) - (i128) s[f[idx]];
}

void getit1() {
	for (int i = 1; i <= n; i++) {
		int inp = read<int>();
		s[i] = s[i - 1] + inp;
	}
}

void getit2() {
	int x = read<int>(), y = read<int>(), z = read<int>();
	b[1] = read<int>(), b[2] = read<int>(), m = read<int>();
	for (int i = 1; i <= m; i++)
		p[i] = read<int>(), l[i] = read<int>(), r[i] = read<int>();
	for (int i = 3; i <= n; i++)
		b[i] = ((1ll * x * b[i - 1] + 1ll * y * b[i - 2]) % P + z) % P;
	p[0] = 0;
	for (int j = 1; j <= m; j++)
		for (int i = p[j - 1] + 1; i <= p[j]; i++) {
			int inp = b[i] % (r[j] - l[j] + 1) + l[j];
			s[i] = s[i - 1] + inp;
		}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	// freopen("partition.in", "r", stdin);
	// freopen("partition.out", "w", stdout);

	n = read<int>(), type = read<int>();
	if (type == 0) getit1();
	else getit2();
	
	f[0] = 0;
	head = 1, tail = 0;
	mtq[++tail] = 0;
	for (int i = 1; i <= n; i++) {
		while (head < tail && v(mtq[head + 1]) <= s[i])
			head++;
		f[i] = mtq[head];
		while (head <= tail && v(mtq[tail]) >= v(i))
			tail--;
		mtq[++tail] = i;
	}
	i128 ans = 0;
	for (int i = n; i; i = f[i])
		ans += (i128) ((i128) s[i] - s[f[i]]) * ((i128) s[i] - s[f[i]]);
	write<i128>(ans);
	puts("");
	return 0;
}
