#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e5 + 7;

int n, q;
int a[N], L[N], ans[N];
std::stack<int> stc;
std::vector<std::pair<int, int>> v[N];

struct Fenwick {
	int tr[N << 1];

	int lowbit(int x) { return x & -x; }

	void add(int i) {
		for (; i <= n; i += lowbit(i))
			tr[i]++;
	}

	int sum(int i) {
		int ret = 0;
		for (; i; i -= lowbit(i))
			ret += tr[i];
		return ret;
	}
} bit;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 1; i <= n; i++) {
		while (!stc.empty() && a[stc.top()] <= a[i])
			stc.pop();
		L[i] = stc.size() ? stc.top() : 1;
		stc.push(i);
	}
	for (int i = 1; i <= q; i++) {
		int l, r;
		std::cin >> l >> r;
		v[r].push_back({l, i});
	}
	for (int i = n; i >= 1; i--) {
		for (auto j : v[i])
			ans[j.second] = bit.sum(j.first);
		bit.add(L[i]);
	}
	for (int i = 1; i <= q; i++)
		std::cout << ans[i] << "\n";
	return 0;
}
