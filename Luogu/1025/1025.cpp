#include <bits/stdc++.h>

using i64 = long long;

int n, k, ans;

void dfs(int lst, int sum, int cur) {
    if (cur == k) {
        if (sum == n)
            ans++;
        return;
    }
    for (int i = lst; i * (k - cur) + sum <= n; i++)
        dfs(i, sum + i, cur + 1);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> k;
    dfs(1, 0, 0);
    std::cout << ans << "\n";
    return 0;
}
