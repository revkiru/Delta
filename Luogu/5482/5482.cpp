#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e6 + 7;
constexpr int M = 1e5 + 7;

int n, cnt, tim;
int c0[N << 1], c1[N << 1], typ[M], k[M];
bool vis[M];

struct Fenwick {
	int lowbit(int x) { return x & -x; }

	void add(int i, int v, int tr[]) {
		i += N;
		for (; i <= (N * 2 - 1); i += lowbit(i))
			tr[i] += v;
	}

	int sum(int i, int tr[]) {
		i += N;
		int ret = 0;
		for (; i; i -= lowbit(i))
			ret += tr[i];
		return ret;
	}
} bit;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	while (n--) {
		int x, y, z;
		std::string s;
		std::cin >> s;
		if (s == "Add") {
			std::cin >> x >> y >> z;
			if (!x) {
				if (y > z) {
					cnt++;
					typ[++tim] = 3;
				} else {
					typ[++tim] = 0;
				}
			}
			if (x > 0) {
				k[++tim] = std::floor((z * 1.0 - y) / x);
				typ[tim] = 1;
				if (k[tim] > 1e6) {
					typ[tim] = 0;
				} else if (k[tim] < -1e6) {
					cnt++;
					typ[tim] = 3;
				} else {
					bit.add(k[tim], 1, c0);
				}
			}
			if (x < 0) {
				k[++tim] = std::ceil((z * 1.0 - y) / x);
				typ[tim] = 2;
				if (k[tim] < -1e6) {
					typ[tim] = 0;
				} else if (k[tim] > 1e6) {
					cnt++;
					typ[tim] = 3;
				} else {
					bit.add(k[tim], 1, c1);
				}
			}
		}
		if (s == "Query") {
			std::cin >> x;
			std::cout << bit.sum(x - 1, c0) + (bit.sum(1e6, c1) - bit.sum(x, c1)) + cnt << "\n";
		}
		if (s == "Del") {
			std::cin >> x;
			if (vis[x])
				continue;
			vis[x] = 1;
			if (typ[x] == 3)
				cnt--;
			if (typ[x] == 1)
				bit.add(k[x], -1, c0);
			if (typ[x] == 2)
				bit.add(k[x], -1, c1);
		}
	}
	return 0;
}
