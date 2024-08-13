#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;
constexpr int R = 30;

int n, m, u, a[R];
int ans = 1;
bool vis[N], buc[N << 8];

void init() {
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= m; j++) {
			u += buc[i * j] ^ 1;
			buc[i * j] = 1;
		}
		a[i] = u;
	}
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	init();
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) {
			int x = i, cnt = 0;	
			while (x <= n) { cnt++; vis[x] = 1; x *= i; }
			ans += a[cnt];
		}
	}
	std::cout << ans << "\n";
	return 0;
}
