#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 3e6 + 7;

int n, p;
int inv[N];

int main() {
	scanf("%d %d", &n, &p);

	inv[1] = 1;
	for (int i = 2; i <= n; i++)
		inv[i] = (i64) (p - p / i) * inv[p % i] % p;
	for (int i = 1; i <= n; i++)
		printf("%d\n", inv[i]);
	return 0;
}
