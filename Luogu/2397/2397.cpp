#include <bits/stdc++.h>

using i64 = long long;

int n, ans, cnt;

int main() {
	scanf("%d", &n);
	for (int i = 1, x; i <= n; i++) {
		scanf("%d", &x);
		if (!cnt) {
			ans = x;
			cnt++;
		} else {
			cnt += (x == ans) ? 1 : -1;
		}
	}
	printf("%d\n", ans);
	return 0;
}
