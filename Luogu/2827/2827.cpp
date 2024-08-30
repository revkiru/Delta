#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int R = 0x3f3f3f3f;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar_unlocked();
	for (; !isdigit(ch); ch = getchar_unlocked()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar_unlocked()) sum = sum * 10 + ch - '0';
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar_unlocked('-'); }
	if (x > 9) write(x / 10);
	putchar_unlocked(x % 10 + '0');
}

int n, m, q, u, v, t;
int qt;
int a[N];
std::queue<int> que[4];

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	n = read<int>(), m = read<int>(), q = read<int>(), u = read<int>(), v = read<int>(), t = read<int>();
	for (int i = 1; i <= n; i++)
		a[i] = read<int>();

	std::sort(a + 1, a + n + 1, std::greater<int>());
	for (int i = 1; i <= n; i++)
		que[1].push(a[i]);

	for (int i = 0; i < m; i++) {
		std::pair<int, int> p = std::max({
			std::make_pair(que[1].empty() ? -R : que[1].front(), 1),
			std::make_pair(que[2].empty() ? -R : que[2].front(), 2),
			std::make_pair(que[3].empty() ? -R : que[3].front(), 3)
		});
		int x = p.first + q * i, j = p.second;
		que[j].pop();
		int b = 1ll * x * u / v, c = x - b;
		que[2].push(b - q - q * i);
		que[3].push(c - q - q * i);
		if (i % t == t - 1) { write<int>(x); putchar(' '); }
	}
	puts("");

	for (int i = 1; i <= n + m; i++) {
		std::pair<int, int> p = std::max({
			std::make_pair(que[1].empty() ? -R : que[1].front(), 1),
			std::make_pair(que[2].empty() ? -R : que[2].front(), 2),
			std::make_pair(que[3].empty() ? -R : que[3].front(), 3)
		});
		int x = p.first, j = p.second;
		que[j].pop();
		if (i % t == 0) { write<int>(x + q * m); putchar(' '); }
	}
	puts("");

	return 0;
}
