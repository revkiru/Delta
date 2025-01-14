#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;
constexpr int P = 1e9 + 7;

int n, mx, cnt;
int a[N], pri[N], phi[N];
int f[N];

template <typename T>
T expow(T a, T b) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * a % P;
		a = a * a % P;
	}
	return ret;
}

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1, x; i <= n; i++) {
		std::cin >> x;
		a[x]++;
		mx = std::max(mx, x);
	}

	phi[1] = 1;
	int U = 0;
	while (mx >= (1 << U))
		U++;
	for (int i = 2; i <= (1 << U); i++) {
		if (!phi[i]) { pri[++cnt] = i; phi[i] = i - 1; }
		for (int j = 1; j <= cnt && i * pri[j] <= (1 << U); j++) {
			if (i % pri[j] != 0)
				phi[i * pri[j]] = phi[i] * phi[pri[j]];
			else {
				phi[i * pri[j]] = phi[i] * pri[j];
				break;
			}
		}
	}

	f[0] = expow(2ll, a[0]);
	int p = 0;
	for (int i = 1; i <= mx; i++) {
		if (a[i]) {
			p |= i;
			int s = p ^ i;
			for (int j = s; ; j = (j - 1) & s) {
				f[i | j] = (f[i | j] + f[j] * a[i]) % P;
				if (!j)
					break;
			}
		}
	}

	int ans = 0;
	for (int i = 0; i < (1 << U); i++)
		ans = (ans + f[i] * phi[i + 1]) % P;
	std::cout << ans << "\n";
	return 0;
}

/*
首先要考虑到这个本质：把一个二进制数看成若干个其在二进制位上所“拥有”的数的集合，要求选取集合时集合两两无交，求选取的合法方案中所选取集合的权值和
注意到 And 为 0 意味着我们可以直接每位累积二进制数，也就是直接并起来而不用进位
设 f_i 为选出集合并集为 i 时的合法选择方案数，枚举子集去做
*/
