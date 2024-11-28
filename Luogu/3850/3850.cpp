#include <bits/stdc++.h>
#include <ext/rope>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, m, q;
std::string t[N << 1];
__gnu_cxx::rope<int> a;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> t[a.size()];
		a.append(a.size());
	}
	std::cin >> m;
	for (int i = 1, x; i <= m; i++) {
		std::cin >> t[a.size()];
		std::cin >> x;
		a.insert(x, a.size());
	}
	std::cin >> q;
	for (int i = 1, x; i <= q; i++) {
		std::cin >> x;
		std::cout << t[a[x]] << "\n";
	}
	return 0;
}
