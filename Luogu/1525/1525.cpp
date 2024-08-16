#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 2e4 + 7;
constexpr int M = 1e5 + 7;

int n, m;
int a[N];

struct node {
	int x, y, z;
} f[M];

bool cmp(const node &p, const node &q) {
	return p.z > q.z;
}

struct UniFind {
	int fa[N];
	
	void init() {
		std::iota(fa + 1, fa + n + 1, 1);
	}
	
	int find(int x) {
		if (x != fa[x]) return fa[x] = find(fa[x]);
		return x;
	}
	
	void merge(int x, int y) {
		int fx = find(x), fy = find(y);
		fa[fx] = fy;
	}
	
	bool check(int x, int y) {
		int fx = find(x), fy = find(y);
		if (fx == fy) return 1;
		return 0;
	}
} uni;

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> m;
	for (int i = 1; i <= m; i++)
		std::cin >> f[i].x >> f[i].y >> f[i].z;
	uni.init();
	std::sort(f + 1, f + m + 1, cmp);
	for (int i = 1; i <= m + 1; i++) {
		if (uni.check(f[i].x, f[i].y)) {
			std::cout << f[i].z << "\n";
			break;
		} else {
			if (!a[f[i].x])
				a[f[i].x] = f[i].y;
			else
				uni.merge(a[f[i].x], f[i].y);
			
			if (!a[f[i].y])
				a[f[i].y] = f[i].x;
			else
				uni.merge(a[f[i].y], f[i].x);
		}
	}
	return 0;
}
