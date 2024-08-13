#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, k, q;
int top, stc[N], a[N];
int L[N][20], R[N][20];


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k >> q;
	for (int i = 1; i <= n; i++)
		std::cin >> a[i];

	top = 0;
	for (int i = 1; i <= n; i++) {
		while (top && a[stc[top]] < a[i])
			top--;
		if (top) L[i][0] = stc[top];
		else L[i][0] = i;
		stc[++top] = i;
	}

	top = 0;
	for (int i = n; i; i--) {
		while (top && a[stc[top]] < a[i])
			top--;
		if (top) R[i][0] = stc[top];
		else R[i][0] = i;
		stc[++top] = i;
	}

	for (int j = 1; j < 18; j++) {
		for (int i = 1; i <= n; i++) {
			L[i][j] = std::min(L[L[i][j - 1]][j - 1], L[R[i][j - 1]][j - 1]);
			R[i][j] = std::max(R[L[i][j - 1]][j - 1], R[R[i][j - 1]][j - 1]);
		}
	}

	while (q--) {
		int x, y, ans = 0;
		std::cin >> x >> y;
		if (x > y) std::swap(x, y);
		int l = x, r = x;
		for (int i = 17; i >= 0; i--) {
			int nl = std::min(L[l][i], L[r][i]);
			int nr = std::max(R[l][i], R[r][i]);
			if (nr < y) {
				l = nl, r = nr;
				ans += (1 << i);
			}
		}

		x = r;
		l = r = y;
		for (int i = 18; i >= 0; i--) {
			int nl = std::min(L[l][i], L[r][i]);
			int nr = std::max(R[l][i], R[r][i]);
			if (nl > x) {
				l = nl, r = nr;
				ans += (1 << i);
			}
		}
		std::cout << ans << "\n";
	}
	return 0;
}
