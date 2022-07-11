from math import gcd


def do2(N=10**18):
    # record largest prime factor of numbers up to cube root of N
    N3 = int(N**(1./3)) + 1  # overestimate is OK
    P = list(range(N3 + 1))
    for p in range(2, (N3 >> 1) + 1):
        if P[p] != p:
            continue
        for j in range(p << 1, N3 + 1, p):
            P[j] = p
    
    print(P)

    # here's how we extract powers of a prime p
    def g(n, x, p, e, ph_e, exp, ph=0, gcd=gcd):
        count = 0
        p_pow = p**exp
        n //= p_pow
        while n:
            count += f(n, x, p, gcd(exp, e), gcd(ph + exp - 1, ph_e))
            p_pow *= p
            n //= p
            exp += 1
        return count

    def f(n, x, m, e, ph_e, P=P, g=g):
        # Gives the count of numbers k<=n that are e-Achilles (i.e. the
        # exponents in k are all >=2 and their gcd is relatively prime to e)
        # with phi(k)*x being ph_e-Achilles, whose largest prime factor is less
        # than m.

        # Deal with the largest prime dividing x
        p = P[x]
        if p > 1:
            count = k = 0
            x_no_p = x
            while not x_no_p % p:
                x_no_p //= p
                k += 1
            if k >= 2:
                count += f(n, x_no_p, p, e, gcd(k, ph_e))
            if p >= m or p * p > n:
                return count  # can't adjust further
            count += g(n, x_no_p * (p - 1), p, e, ph_e, 2, k)
        else:
            # include here the number with no prime factors, when appropriate
            count = int(e == ph_e == 1)

        # Or we can introduce other primes larger than p
        if (p + 1)**3 > n:
            return count  # all such primes are too big
        n3 = int((n if e else n >> 2)**(1./3)) + \
            2  # must be > cuberoot, <= N3+1
        if m > n3:
            m = n3
        for q in range(p + 1, m):
            if P[q] != q:
                continue
            count += g(n, x * (q - 1), q, e, ph_e, 3)
        return count
    return f(N - 1, 1, N, 0, 0)


print(do2())
