from random import randint
from time import perf_counter

MY_NUM = 181552877565998943910618543225528579935321447209736978912489118450818545230489


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def miller_rabin_test(a, n, s, d):
    x = pow(a, d, n)
    if x in (1, n - 1):
        return True
    for r in range(s - 1):
        x = (x * x) % n
        if x == 1:
            return False
        elif x == n - 1:
            return True
    return False


def miller_rabin(n):
    s, d = 0, n - 1
    while d % 2 == 0:
        s, d = s + 1, d // 2
    for _ in range(n.bit_length()):
        a = randint(2, n - 2)
        if not miller_rabin_test(a, n, s, d):
            return False
    return True


def pollards_rho_iter(n):
    x = y = 2
    a = 1
    while True:
        d = 1
        while d == 1:
            x = (x * x + a) % n
            y = (y * y + a) % n
            y = (y * y + a) % n
            d = gcd(n, abs(x - y))
        if d < n:
            return d
        x = y = randint(1, n - 1)
        a = randint(-100, 100) % n


def factor(n):
    ans = []
    for x in (2, 3, 5, 7, 11, 13):
        while n % x == 0:
            ans.append(x)
            n //= x
    if n == 1:
        pass
    elif miller_rabin(n):
        ans.append(n)
    else:
        d = pollards_rho_iter(n)
        ans.extend(factor(d))
        ans.extend(factor(n // d))
    return sorted(ans)


nums = [10, 437, 3127, 23707, 1752967, 6682189, 12659363, 494370889, 1435186847, MY_NUM]
for num in nums:
    st = perf_counter()
    fct = factor(num)
    en = perf_counter()
    print('Число {} разложено на множители {} за {:02f}c'.format(num, fct, en-st))