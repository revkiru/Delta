#include <bits/stdc++.h>

using i64 = long long;

i64 w, h, n;
std::set<i64> lx, ly;	// line: 切割位置
std::multiset<i64> bx, by;	// block: 碎块边长

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> w >> h >> n;
	bx.insert(w);
	by.insert(h);

	lx.insert({0, w});
	ly.insert({0, h});

	for (int i = 1; i <= n; i++) {
		char c;
		i64 t;
		std::cin >> c >> t;
		if (c == 'H') {
			ly.insert(t);
			auto it = ly.find(t);
			i64 l = *(--it);
			i64 r = *(++(++it));
			it = by.find(r - l);
			by.erase(it);
			by.insert({r - t, t - l});
		} else {
			lx.insert(t);
			auto it = lx.find(t);
			i64 l = *(--it);
			i64 r = *(++(++it));
			it = bx.find(r - l);
			bx.erase(it);
			bx.insert({r - t, t - l});
		}

		auto it = bx.end();
		i64 l = *(--it);
		it = by.end();
		i64 r = *(--it);
		std::cout << l * r << "\n";
	}

	return 0;
}
