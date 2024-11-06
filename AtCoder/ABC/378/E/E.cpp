#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using i64 = long long;
using i128 = __int128;

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

template <typename K, typename V, typename Comp = std::less<K>>
using ordered_map = __gnu_pbds::tree<
  K, V, Comp,
  __gnu_pbds::rb_tree_tag,
  __gnu_pbds::tree_order_statistics_node_update
>;

template <typename K, typename Comp = std::less<K>>
using ordered_set = ordered_map<K, __gnu_pbds::null_type, Comp>;

constexpr int N = 2e5 + 7;

int n, m;
int a[N], pre[N];
i128 ans, sum;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		pre[i + 1] = (pre[i] + a[i]) % m;
	}
	ordered_set<std::pair<int, int>> s;
	for (int i = 0; i <= n; i++) {
		auto idx = std::make_pair(pre[i], i);
		int val = int(s.size()) - int(s.order_of_key(idx));
		s.insert(idx);
		ans += (i128) pre[i] * i + (i128) val * m - sum;
		sum += pre[i];
	}
	write<i128>(ans);
	puts("");
	return 0;
}
