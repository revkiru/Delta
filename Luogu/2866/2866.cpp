#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 8e4 + 7;

int n;
std::stack<int> stc;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    i64 ans = 0;
    for (int i = 1, x; i <= n; i++) {
        std::cin >> x;
        while (!stc.empty() && (stc.top() <= x))
            stc.pop();
        ans += stc.size();
        stc.push(x);
    }
    std::cout << ans << "\n";
    return 0;
}
