#include <bits/stdc++.h>

using i64 = long long;

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> p(3, std::vector<int>(n + 1));
    for (int i = 0; i < 3; i++)
        for (int j = 1; j <= n; j++)
            std::cin >> p[i][j];

    std::string s = "qkj";
    std::vector<std::pair<char, int>> ans(n + 1, {'\0', -1});

    std::vector<int> mns(3, n);
    for (int i = n - 1; i >= 1; i--) {
        int flg = -1;
        for (int j = 0; j < 3; j++)
            if (p[j][i] > p[j][mns[j]])
                flg = j;
        if (flg == -1) continue;
        ans[i] = {s[flg], mns[flg]};
        for (int j = 0; j < 3; j++)
            if (p[j][i] < p[j][mns[j]])
                mns[j] = i;
    }

    if (ans[1].second == -1) { std::cout << "NO\n"; return; }
    std::cout << "YES\n";
    std::vector<std::pair<char, int>> output = {ans[1]};
    while (output.back().second >= 0) {
        output.push_back(ans[output.back().second]);
    }
    output.pop_back();
    std::cout << output.size() << "\n";
    for (auto &[c, i] : output) {
        std::cout << c << " " << i << "\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
