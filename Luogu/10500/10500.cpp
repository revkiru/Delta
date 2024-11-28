#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n;
int a[N], b[N];
double ansXor, ansAnd, ansOr;

void Rainbow(int k) {
	int lst[2] = {0, 0};
	int c1 = 0, c2 = 0;
	double w = (double) (1 << k) / n / n;
	for (int i = 1; i <= n; i++) {
		b[i] = ((a[i] >> k) & 1);
		if (b[i]) { ansXor += w; ansAnd += w; ansOr += w; }
		if (!b[i])
			ansOr += w * lst[1] * 2;
		else {
			ansAnd += w * (i - 1 - lst[0]) * 2;
			ansOr += w * (i - 1) * 2;
		}
		ansXor += w * (b[i] ? c1 : c2) * 2;
		c1++;
		if (b[i])
			std::swap(c1, c2);
		lst[b[i]] = i;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];
	for (int i = 0; i < 31; i++)
		Rainbow(i);
	std::cout << std::fixed << std::setprecision(3)
		<< ansXor << " " << ansAnd << " " << ansOr << "\n";
	return 0;
}
