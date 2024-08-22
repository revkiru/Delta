#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e7 + 7;

int n, k, seed, S;
int p[N << 1], sum[N << 2];

int getrand() {
	seed = ((seed * 12321) ^ 9999) % 32768;
	return seed;
}

void generateData() {
	std::cin >> k >> seed >> S;
	int t = 0;
	n = (k << 1) + 1;
	for (int i = 1; i <= n; i++) {
		p[i] = (getrand() / 128) % 2;
		t += p[i];
	}
	int i = 1;
	while (t > k) {
		while (p[i] == 0) i++;
		p[i] = 0;
		t--;
	}
	while (t < k) {
		while (p[i] == 1) i++;
		p[i] = 1;
		t++;
	}
}	

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	generateData();
	int u = 0;
	// for (int i = 1; i <= n; i++)
	// 	std::cout << p[i] << " ";
	std::cout << "\n";
	for (int i = 1; i <= n; i++) {
		u += (p[i] ? 1 : -1);
		// std::cout << n + u << " ";
		sum[n + u] += p[i];
		// std::cout << p[i] << "\n";
	}

	int res = 0;
	for (int i = 1; i <= n; i++)
		res += sum[n + i];

	int lst = 1;
	int ans1 = 0, ans2 = 0, ans3 = 0;
	for (int i = 1; i <= n; i++) {
		u += (p[i] ? 1 : -1);
		if (lst > u + 2) { res += sum[n + u + 2]; }
		if (lst < u + 2) { res -= sum[n + lst]; }
		if (res == 0 && !p[i]) ans1 = i;
		if (res == S && !p[i]) ans2 = i;
		if (res == k - S && !p[i]) ans3 = i;
		if (ans1 && ans2 && ans3) break;
		sum[n + u + 1] -= p[i];
		sum[n + u] += p[i];
		lst = u + 2;
	}

	std::cout << ans1 << "\n" << ans2 << "\n" << ans3 << "\n";
	return 0;
}
