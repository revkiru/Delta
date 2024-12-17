#include <bits/stdc++.h>

using i64 = long long;

constexpr int N = 5e5 + 7;

int n, k;

char recd() { char o; while ((o = getchar()) < 'A' || o > 'Z'); return o; }

struct ChtollyTree {
	struct Node_t {
		int l, r;
		mutable int v;
		
		bool operator < (const Node_t &x) const {
			return l < x.l;
		}
	};
	std::set<Node_t> s;

	auto split(int p) {
		auto it = std::prev(s.upper_bound({p, p, 0}));
		if (it != s.end() && it->l == p)
			return it;
		int l = it->l, r = it->r, v = it->v;
		s.erase(it);
		s.insert({l, p - 1, v});
		return s.insert({p, r, v}).first;
	}
	
	void assign(int l, int r, int v) {
		auto _l = std::prev(s.upper_bound({l, 0, 0}));
		auto _r = std::prev(s.upper_bound({r, 0, 0}));
		/* merge right */
		if (_r != std::prev(s.end()) && _r->r == r && v == (_r = std::next(_r))->v) {
			r = _r->r;
			_r = std::next(_r);
		} else if (_r->v != v) {
			_r = split(r + 1);
			_l = std::prev(s.upper_bound({l, 0, 0}));
		} else {
			r = _r->r;
			_r = std::next(_r);
		}
		/* merge left */
		if (_l != s.begin() && _l->l == l && v == (std::prev(_l))->v) {
			_l = std::prev(_l);
			l = _l->l;
		}
		if (_l->v != v)
			_l = split(l);
		else
			l = _l->l;
		s.erase(_l, _r);
		s.insert({l, r, v});
	}
	
	bool judge(int l, int r) {
		auto p = std::prev(s.upper_bound({l, 0, 0}));
		if (p != std::prev(s.upper_bound({r, 0, 0})))
			return 0;
		if (!(l != 1 && r != n))
			return 1;
		if (l > p->l && r < p->r)
			return 0;
		if (l == p->l && r != p->r)
			return std::prev(p)->v != p->v;
		if (r == p->r && l != p->l)
			return std::next(p)->v != p->v;
		return std::prev(p)->v != std::next(p)->v;
	}
} odt;

int main() {
	scanf("%d", &n);
	int l = 1, r = 1, p = n - 1;
	char prec, w;
	scanf(" %1c", &prec);
	while (p--) {
		scanf(" %1c", &w);
		if (w == prec) { r++; continue; }
		odt.s.insert({l, r, prec});
		l = ++r;
		prec = w;
	}
	odt.s.insert({l, r, prec});

	scanf("%d", &k);
	while (k--) {
		char x;
		scanf(" %1c %d %d", &w, &l, &r);
		if (w == 'A') {
			scanf(" %1c", &x);
			odt.assign(l, r, x);
		} else {
			printf("%s\n", (odt.judge(l, r) ? "Yes" : "No"));
		}
	}
	return 0;
}
