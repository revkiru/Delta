#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

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

int n, m;
int a[N], mp[N];

void mexIt(int lst = 0) {
	memset(mp, 0 , sizeof(mp));
	for (int i = 1; i <= n; i++)
		if (a[i] <= n)
			mp[a[i]]++;
	while (mp[lst])
		lst++;
	for (int i = 1; i <= n; i++) {
		if (a[i] > lst || mp[a[i]] >= 2)
			a[i] = lst;
	}
}

void solve() {
	n = read<int>(), m = read<int>();
	for (int i = 1; i <= n; i++)
		a[i] = read<int>();

	if (m == 1) { mexIt(); }
	else if (m & 1) { for (int i = 1; i <= 3; i++) mexIt(); }
	else { for (int i = 1; i <= 2; i++) mexIt(); }

	for (int i = 1; i <= n; i++) {
		write<int>(a[i]);
		putchar(' ');
	}
	puts("");
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	// freopen("rabbit.in", "r", stdin);
	// freopen("rabbit.out", "w", stdout);

	int t = read<int>();
	while (t--) {
		solve();
	}
	return 0;
}
