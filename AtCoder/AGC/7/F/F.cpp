#include <bits/stdc++.h>

using i64 = long long;

int n, ans;
std::string s, t;
std::queue<int> q;


int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	std::cin >> s >> t;

	if (s == t) { std::cout << "0\n"; exit(0); }

	int l = n - 1, r = n - 1;
	while (r >= 0) {
		while (r >= 1 && t[r - 1] == t[r]) r--;	// 当前折线在最后一行最左的位置
		while (l >= 0 && (l > r || s[l] != t[r])) l--;	// 当前折线第一行最左边的位置
		if (l < 0) { std::cout << "-1\n"; exit(0); }
		while (!q.empty() && q.front() - q.size() >= r) q.pop();	// 当前折线不会触及的位置
		if (l != r) q.push(l);	// 真折线而不是竖直向下
		ans = std::max(ans, (int) q.size() + 1);
		r--;
	}
	std::cout << ans << "\n";
	return 0;
}
