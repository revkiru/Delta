#include <bits/stdc++.h>

constexpr int N = 1e5 + 7;

using i64 = long long;

int n, k, ans;
int fa[N], re[N];

int find(int x) {
	int par = fa[x];
	if (par != x) {
		fa[x] = find(par);
		re[x] = (re[x] + re[par]) % 3;
		return fa[x];
	}
	return par;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);
	
	int n, k;
	std::cin >> n >> k;
	std::iota(fa + 1, fa + n + 1, 1);
	for (int i = 1; i <= k; i++) {
		int opt, x, y;
		std::cin >> opt >> x >> y;
		if ((x > n || y > n) || (opt == 2 && x == y)) {
			ans++;
			continue;
		}
		if (opt == 1) {
			int f1 = find(x), f2 = find(y);
			if (f1 == f2 && re[x] != re[y]) {
				ans++;
				continue;
			} else if (f1 != f2) {
				fa[f1] = f2;
				re[f1] = (3 - re[x] + re[y]) % 3;
			}
		}
		if (opt == 2) {
			int f1 = find(x), f2 = find(y);
			if (f1 == f2) {
				int rel = (re[x] - re[y] + 3) % 3;
				if (rel != 1) {
					ans++;
					continue;
				}
			} else {
				int fo = find(x), ft = find(y);
				fa[fo] = ft;
				re[fo] = (3 - re[x] + re[y] + 1) % 3;
			}
		}
	}	
	std::cout << ans << "\n";
	return 0;
}
