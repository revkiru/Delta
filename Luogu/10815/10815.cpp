#include <bits/stdc++.h>

using i64 = long long;

template <typename T> T read() {
	T sum = 0, fl = 1;
	int ch = getchar();
	for (; !isdigit(ch); ch = getchar()) { if (ch == '-') fl = -1; }
	for (; isdigit(ch); ch = getchar()) { sum = 1ll * sum * 10 + (ch - '0'); }
	return sum * fl;
}

template <typename T> void write(T x) {
	if (x < 0) { x = -x; putchar('-'); }
	if (x > 9) { write(x / 10); }
	putchar(x % 10 + '0');
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int n = read<int>();
	i64 sum = 0;
	while (n--) {
		int x = read<int>();
		sum += x;
	}
	write<i64>(sum);
	puts("");
	return 0;
}
