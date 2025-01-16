#include <bits/stdc++.h>

constexpr int N = 1e5 + 7;

int n;

struct node {
	int a, b;

	friend bool operator < (const node &a, const node &b) {
		return a.a * a.b < b.a * b.b;
	}
} t[N];

std::string exstr(int qs) {
	std::string res = "";
	while (qs) {
		res += qs % 10 + '0';
		qs /= 10;
	}
	std::reverse(res.begin(), res.end());
	return res;
}

std::string strmax(std::string a, std::string b) {
	if (a.size() != b.size()) {
		return a.size() > b.size() ? a : b;
	}
	return a > b ? a : b;
}

int dvs[N << 1], dvrs[N << 1];

std::string strdiv(std::string a, const int b) {
	memset(dvs, 0, sizeof(dvs));
	memset(dvrs, 0, sizeof(dvrs));
	for (int i = 0; i < a.size(); i++) {
		dvs[i + 1] = a[i] - '0';
	}
	int bs = 0;
	for (int i = 1; i <= a.size(); i++) {
		dvrs[i] = (bs * 10 + dvs[i]) / b;
		bs = (bs * 10 + dvs[i]) % b;
	}
	int ln = 1;
	while (dvrs[ln] == 0 && ln < a.size()) {
		++ln;
	}
	std::string div_ans;
	for (int i = ln; i <= a.size(); i++) {
		div_ans += dvrs[i] + '0';
	}
	return div_ans;
}

int res[N << 1];

std::string strmul(std::string a, std::string b) {
	std::reverse(a.begin(), a.end());
	std::reverse(b.begin(), b.end());
	memset(res,  0, sizeof(res));
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++)
			res[i + j] += (a[i] - '0') * (b[j] - '0');
	}
	for (int i = 0; i < a.size() + b.size(); i++) {
		if (res[i] >= 10) {
			res[i + 1] += res[i] / 10;
			res[i] %= 10;
		}
	}
	std::string revstr;
	bool flg = 1;
	for (int i = a.size() + b.size() - 1; i >= 0; i--) {
		if (res[i] == 0 && flg)
			continue;
		else {
			flg = 0;
			revstr += res[i] + '0';
		}
	}
	return revstr;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> n;
	for (int i = 0; i <= n; i++) {
		std::cin >> t[i].a >> t[i].b;
	}
	std::sort(t + 1, t + n + 1);
	std::string ans;
	std::string mul = exstr(t[0].a);
	for (int i = 1; i <= n; i++) {
		ans = strmax(ans, strdiv(mul, t[i].b));
		mul = strmul(mul, exstr(t[i].a));
	}

	std::cout << ans << "\n";
	return 0;
}
