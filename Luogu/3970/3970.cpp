#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 1e5 + 7;
constexpr int P = 1e9 + 7;

int n, t0t;
int a[N], b[N];
i64 dp[N], lastAns[N];

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

std::unordered_map<i64, i64, custom_hash> mp;

template <typename T>
struct Fenwick {
	T tr[N << 2];

	T lowbit(T x) { return x & -x; }

	void add(T i, T x) {
		for (; i <= n; i += lowbit(i)) {
			(tr[i] += x) %= P;
		}
	}

	T query(T i) {
		int res = 0;
		for (; i; i -= lowbit(i)) {
			(res += tr[i]) %= P;
		}
		return (res % P);
	}
};

Fenwick<i64> bit;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		b[i] = a[i];
	}

	std::sort(b + 1, b + n + 1);
	t0t = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= t0t; i++)
		mp[b[i]] = i;

	i64 ans = 0;
	for (int i = 1; i <= n; i++) {
		int p = mp[a[i]];
		if (!dp[p]) {
			i64 lst = bit.query(p - 1);
			(ans += lst) %= P;
			bit.add(p, lst + 1);
			lastAns[p] = lst;
			dp[p] = 1;
			continue;
		}
		i64 lst = bit.query(p - 1);
		(ans += (lst - lastAns[p])) %= P;
		bit.add(p, (lst - lastAns[p]) % P);
		lastAns[p] = lst;
	}
	std::cout << ans << "\n";
	return 0;
}
