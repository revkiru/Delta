#include <bits/stdc++.h>

using i64 = long long;

i64 a, m, b;

template <typename T>
T expow(T a, T b, const T P) {
    T ret = 1;
    for (; b; b >>= 1) {
        if (b & 1) ret = ret * a % P;
        a = a * a % P;
    }
    return ret;
}

i64 ModRead(const i64 m) {
    i64 x = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch)) ch = getchar();
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        if (x >= m) f = 1;
        x %= m;
        ch = getchar();
    }
    return x + (f ? m : 0);
}

i64 Phi(i64 n) {
    i64 res = n;
    for (i64 i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            res = res / i * (i - 1);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        res = res / n * (n - 1);
    return res;
}

int main() {
    scanf("%lld %lld", &a, &m);
    b = ModRead(Phi(m));
    printf("%lld\n", expow(a, b, m));
    return 0;
}
