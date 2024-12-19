#include <bits/stdc++.h>

using i64 = long long;

int n, ans;

int main() {
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++) {
        scanf("%d", &x);
        ans = std::__gcd(ans, std::abs(x));
    }
    printf("%d\n", ans);
    return 0;
}
