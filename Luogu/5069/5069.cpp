#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, q;
i64 ans;
int a[N];

std::set<int> s;

struct Fenwick {
	i64 tr[N << 1];

	int lowbit(int x) { return x & -x; }

	void add(int i, i64 v) {
		for (; i <= n; i += lowbit(i))
			tr[i] += v;
	}

	i64 sum(int i) {
		i64 ret = 0;
		for (; i; i -= lowbit(i))
			ret += tr[i];
		return ret;
	}
} bit[2];

bool check(int x) {
	return (a[x - 1] < a[x] && a[x] >= a[x + 1]) || (a[x - 1] >= a[x] && a[x] < a[x + 1]);
}

i64 calc(int x) {
	if (x < 1 || x > n)
		return 0;
	auto it = s.find(x);
	if (*it == 1) {
		auto nxt = it;
		++nxt;
		if (a[*it] < a[*nxt]) {
			return bit[*nxt & 1].sum(*nxt - 1) - bit[*nxt & 1].sum(*it - 1);
		}
		return 0;
	}
	if (*it == n) {
		auto pre = it;
		--pre;
		if (a[*pre] >= a[*it]) {
			return bit[*pre & 1].sum(*it) - bit[*pre & 1].sum(*pre - 1);
		}
		return a[n];
	}
	auto pre = it, nxt = it;
	--pre, ++nxt;
	if (a[*pre] >= a[*it] && a[*it] < a[*nxt]) {
		return bit[*pre & 1].sum(*it - 1) - bit[*pre & 1].sum(*pre - 1) + bit[*nxt & 1].sum(*nxt - 1) - bit[*nxt & 1].sum(*it) + ((*pre & 1) == (*it & 1) && (*nxt & 1) == (*it & 1) ? a[*it] : 0);
	}
	return 0;
}

void add(int pre, int nxt) {
	auto l = s.find(pre);
	auto r = s.upper_bound(nxt);
	while (l != r)
		ans += calc(*l++);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		bit[i & 1].add(i, a[i]);
	}
	s.insert(-2); s.insert(-1); s.insert(n + 2); s.insert(n + 3);
	s.insert(1);
	for (int i = 2; i < n; i++) {
		if (check(i))
			s.insert(i);
	}
	s.insert(n);
	for (auto it = s.begin(); it != s.end(); it++)
		ans += calc(*it);

	std::cin >> q;
	while (q--) {
		int k, v;
		std::cin >> k >> v;
		int pre = *--s.lower_bound(k), nxt = *s.upper_bound(k);
		ans -= calc(pre) + calc(nxt);
		pre = *--s.lower_bound(pre), nxt = *s.upper_bound(nxt);
		ans -= calc(pre) + calc(nxt);
		if (s.count(k)) {
			ans -= calc(k);
			s.erase(k);
		}
		s.erase(k - 1); s.erase(k + 1);
		bit[k & 1].add(k, v - a[k]);
		a[k] = v;
		for (int i = k - 1; i <= k + 1; i++) {
			if ((i > 0 && i <= n) && (i == 1 || i == n || check(i)))
				s.insert(i);
		}
		add(pre, nxt);
		std::cout << ans << "\n";
	}
	return 0;
}
