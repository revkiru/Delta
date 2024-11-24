#include <bits/stdc++.h>
#include <ext/rope>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int f[N];

__gnu_cxx::rope<int> tr;

struct Fenwick {
	int tr[N << 1];

	int lowbit(int x) { return x & -x; }

	void add(int i, int v) {
		for (; i <= n; i += lowbit(i)) {
			tr[i] = std::max(tr[i], v);
		}
	}

	int sum(int i) {
		int ret = 0;
		for (; i; i -= lowbit(i)) {
			ret = std::max(ret, tr[i]);
		}
		return ret;
	}
} bit;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		tr.insert(x, i);
	}
	for (int i = 0, x; i < n; i++) {
		x = tr[i];
		bit.add(x, f[x] = bit.sum(x) + 1);
	}
	for (int i = 1; i <= n; i++) {
		std::cout << (f[i] = std::max(f[i], f[i - 1])) << "\n";
	}
	return 0;
}
