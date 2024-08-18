#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;

int n, b, p;
int a[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

std::unordered_map<int, int, custom_hash> mp;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	
	std::cin >> n >> b;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		if (a[i] == b)
			p = i;
	}

	int sl = 0, sr = 0;
	i64 ans = 0;

	for (int i = p; i >= 1; i--) {
		if (a[i] < b) sl--;
		if (a[i] > b) sl++;
		mp[sl]++;
	}
	for (int i = p; i <= n; i++) {
		if (a[i] < b) sr--;
		if (a[i] > b) sr++;
		ans += mp[0 - sr];
	}
	std::cout << ans << "\n";
	return 0;
}
