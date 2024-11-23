#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e7 + 7;

int m;
int pri[N], v[N], phi[N];

template <typename T>
T exmul(T a, T b, const T P) {
	int ret = 0;
	for (; b; b >>= 1) {
		if (b & 1) ret = ((ret % P) + (a % P)) % P;
		a = ((a % P) + (a % P)) % P;
	}
	return ret;
}

template <typename T>
T expow(T a, T b, const T P) {
	T ret = 1;
	for (; b; b >>= 1) {
		if (b & 1) ret = exmul(ret, a, P);
		a = exmul(a, a, P);
	}
	return ret;
}

void myPhi() {
	const int R = 1e7;
	phi[1] = 1;
	for (int i = 2; i <= R; i++) {
		if (v[i] == 0) {
			v[i] = i; pri[++m] = i;
			phi[i] = i - 1;
		}
		for (int j = 1; j <= m; j++) {
			if (pri[j] > v[i] || pri[j] > R / i)
				break;
			v[i * pri[j]] = pri[j];
			phi[i * pri[j]] = phi[i] * (i % pri[j] ? pri[j] - 1 : pri[j]);
		}
	}
}

int solve(const int mod) {
	if (mod == 1) { return 0; }
	return expow(2, solve(phi[mod]) + phi[mod], mod);
}

void work() {
	int p;
	std::cin >> p;
	std::cout << solve(p) << "\n";
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	int t;
	std::cin >> t;
	myPhi();
	while (t--) {
		work();
	}
	return 0;
}