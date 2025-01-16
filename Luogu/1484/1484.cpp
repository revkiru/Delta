#include <bits/stdc++.h>

#define int long long

constexpr int N = 6e5 + 7;

int n, k, ans;
int a[N], l[N], r[N];
bool vis[N];

struct node {
	int v, id;

	bool operator < (const node &rhs) const {
		return v < rhs.v;
	}
};

std::priority_queue<node> q;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		std::cin >> a[i];
		q.push({a[i], i});
		l[i] = i - 1, r[i] = i + 1;
	}
	l[1] = r[n] = 0;

	int len = n;
	for (int i = 1; i <= k; i++) {
		while (!q.empty() && vis[q.top().id])
			q.pop();
		if (q.empty() || q.top().v < 0)
			break;
		auto t = q.top();
		q.pop();
		ans += t.v;
		vis[t.id] = vis[l[t.id]] = vis[r[t.id]] = 1;
		a[++len] = a[l[t.id]] + a[r[t.id]] - a[t.id];
		l[len] = l[l[t.id]], r[len] = r[r[t.id]];
		l[r[len]] = len, r[l[len]] = len;
		q.push({a[len], len});
	}

	std::cout << ans << "\n";
	return 0;
}
