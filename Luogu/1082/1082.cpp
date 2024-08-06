#include <bits/stdc++.h>

using i64 = long long;

template <typename T>
void exgcd(T a, T b, T &x, T &y) {
	if (b == 0) { x = 1, y = 0; return; }
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	i64 a, b, x, y;
	std::cin >> a >> b;
	exgcd(a, b, x, y);
	x = (x % b + b) % b;
	std::cout << x << "\n";
	return 0;	
}
