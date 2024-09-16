#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;

int n, m;
int j, nex[N];
std::string a, b;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> a >> b;

    n = a.size();
    a = '$' + a;
    m = b.size();
    b = '$' + b;

    for (int i = 2; i <= m; i++) {
        while (j && (b[i] != b[j + 1]))
            j = nex[j];
        if (b[j + 1] == b[i])
            j++;
        nex[i] = j;
    }

    j = 0;
    for (int i = 1; i <= n; i++) {
        while (j && (a[i] != b[j + 1]))
            j = nex[j];
        if (b[j + 1] == a[i])
            j++;
        if (j == m) {
            std::cout << i - m + 1 << "\n";
            j = nex[j];
        }
    }

    for (int i = 1; i <= m; i++)
        std::cout << nex[i] << " ";
    std::cout << "\n";
    return 0;
}
