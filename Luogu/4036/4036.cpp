#include <bits/stdc++.h>

using i64 = long long;

int n, m;
std::string s;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> s;
	n = s.size();
	std::cin >> m;
	for (int t = 1, x, d; t <= m; t++) {
		std::string opt, c;
		std::cin >> opt >> x;
		if (opt == "Q") {
			std::cin >> d;
			x--, d--;
			int lcq = 0;
			for (int i = x, j = d; i < n && j < n; i++, j++) {
				if (s[i] == s[j])
					lcq++;
				else
					break;
			}
			std::cout << lcq << "\n";
		}
		if (opt == "R") {
			std::cin >> c;
			s[x - 1] = c[0];
		}
		if (opt == "I") {
			std::cin >> c;
			s.insert(x, c);
			n = s.size();
		}
	}
	return 0;
}
