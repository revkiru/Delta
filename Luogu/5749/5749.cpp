#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e5 + 7;

int n;
i64 ans;
int a[N], t[N];
bool vis[N];
std::vector<int> vec[N << 1];

struct Fenwick {
	int tr[N << 1];

	int lowbit(int x) { return x & -x; }

	void add(int i, int x) {
		for (; i <= n; i += lowbit(i))
			tr[i] += x;
	}

	int query(int i) {
		int res = 0;
		for (; i; i -= lowbit(i))
			res += tr[i];
		return res;
	}
} bit;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	n <<= 1;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		vec[a[i] + n].push_back(i);
		bit.add(i, 1);
	}	
	for (int i = n; i >= 1; i--) {
		if (vis[i])
			continue;
		vis[i] = 1;
		vec[a[i] + n].pop_back();
		int res = vec[n - a[i]].back();
		vec[n - a[i]].pop_back();
		vis[res] = 1;
		ans = ans + (i64) (bit.query(i - 1) - bit.query(res)) + ((a[i] < 0) ? 1 : 0);
		bit.add(res, -1);
	}
	std::cout << ans << "\n";
	return 0;
}
