import math
import sys

sys.set_int_max_str_digits(1000000)

ans = 0
n, m = map(int, input().split())

def fac(x):
    return math.factorial(x)

def A(x, y):
    return fac(x) // fac(x - y)

if (n + 1 >= 2 and n + 3 >= m):
    ans += fac(n) * A(n + 1, 2) * A(n + 3, m)
if (n + 2 >= m - 1 and m >= 1):
    ans += fac(n) * (n + 1) * 2 * m * A(n + 2, m - 1)

print(ans)
