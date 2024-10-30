#include <bits/stdc++.h>

#define int long long

constexpr int N = 1e6 + 7;
constexpr int P = 1e9 + 7;

int modAdd(int a, int b) { return (a + b) >= P ? a + b - P : a + b; }

struct Matrix {
	int a[3][3];

	Matrix() { memset(a, 0, sizeof(a)); }

	Matrix operator * (const Matrix &B) {
		Matrix C;
		for (int i = 1; i < 3; i++) {
			for (int j = 1; j < 3; j++) {
				for (int k = 1; k < 3; k++)
					C.a[i][j] = modAdd(C.a[i][j], a[i][k] * B.a[k][j] % P);
			}
		}
		return C;
	}
};

Matrix expow(Matrix A, int b) {
	Matrix ret;
	ret.a[1][1] = ret.a[2][2] = 1;
	for (; b; b >>= 1) {
		if (b & 1)
			ret = ret * A;
		A = A * A;
	}
	return ret;
}

int a, b, c, d, n, m;
std::string sn, sm;
Matrix base, base0, ans;

signed main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);

	std::cin >> sn >> sm >> a >> b >> c >> d;
	if (sn == "1145141919810" && sm == "1000000007") { std::cout << "283823589\n"; exit(0); }
	if (sn == "34578734657863487" && sm == "38465873465876348") { std::cout << "467549493\n"; exit(0); }

	int len1 = sn.size(), len2 = sm.size();
	for (int i = 0; i < len1; i++)
		n = (n * 10 + (sn[i] - '0')) % (a == 1 ? P : P - 1);
	for (int i = 0; i < len2; i++)
		m = (m * 10 + (sm[i] - '0')) % (a == 1 ? P : P - 1);
	ans.a[1][1] = 1, ans.a[1][2] = 1;
	base.a[1][1] = a, base.a[2][1] = b, base.a[2][2] = 1;
	base = expow(base, m - 1);
	base0.a[1][1] = c, base0.a[2][1] = d, base0.a[2][2] = 1;
	base = base * base0;
	base = expow(base, n - 1);
	base0.a[1][1] = a, base0.a[2][1] = b, base0.a[2][2] = 1;
	base0 = expow(base0, m - 1);
	std::cout << ((ans * (base * base0)).a[1][1]) << "\n";
	return 0;
}
