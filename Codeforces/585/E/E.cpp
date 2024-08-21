#include <bits/stdc++.h>
 
using i64 = long long;
 
constexpr int N = 5e5 + 7;
constexpr int M = 1e7 + 7;
constexpr int P = 1e9 + 7;
 
int n, ans, lim, t0t;
int a[N], lg2[N];
int s[M], tot[M], g[M], pri[M], myu[M];
bool vis[M];
 
void modit(int &x) { x += x >> 31 & P; }
 
void pre() {
	lg2[0] = 1;
	for (int i = 1; i <= N - 7; i++) {
		modit(lg2[i] = lg2[i - 1] * 2 - P);
	}
}
 
void init(const int n) {
	myu[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) { pri[++t0t] = i; myu[i] = -1; }
		for (int j = 1; j <= t0t && i * pri[j] <= n; j++) {
			vis[i * pri[j]] = 1;
			if (i % pri[j] == 0) {
				myu[i * pri[j]] = 0;
				break;
			} else
				myu[i * pri[j]] = -myu[i];
		}
	}
}
 
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
 
	pre();
	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		tot[a[i]]++;
	}
	
	lim = *std::max_element(a + 1, a + n + 1);
	init(lim);
	for (int i = 1; i <= t0t; i++) {
		for (int j = lim / pri[i]; j; j--)
			tot[j] += tot[j * pri[i]];
	}
	for (int i = 1; i <= lim; i++)
		g[i] = tot[i] * myu[i];
	for (int i = 1; i <= t0t; i++) {
		for (int j = 1; j * pri[i] <= lim; j++)
			g[j * pri[i]] += g[j];
	}
	for (int i = 1; i <= lim; i++)
		s[i] = lg2[tot[i]] - 1;
	for (int i = t0t; i; i--) {
		for (int j = 1; j * pri[i] <= lim; j++) {
			modit(s[j] -= s[j * pri[i]]);
		}
	}
	for (int i = lim; i > 1; i--)
		ans = (ans + 1ll * s[i] * g[i]) % P;
	std::cout << ans << "\n";
	return 0;
}

