def Eratosthenes(n):
    res = 1
    k = n
    n = min(15476299, 16 * n)
    prime = [True] * (n + 1)
    for i in range(4, n + 1, 2):
        prime[i] = False
    tmp = 1
    tmp2 = 2 ** (2 ** tmp)
    while tmp2 <= n:
        prime[tmp2] = True
        tmp += 1
        tmp2 = 2 ** (2 ** tmp)
    p = 3
    while p * p <= n:
        if prime[p]:
            for i in range(p * p, n + 1, p):
                prime[i] = False
            tmp = 1
            tmp2 = p ** (2 ** tmp)
            while tmp2 <= n:
                prime[tmp2] = True
                tmp += 1
                tmp2 = p ** (2 ** tmp)
        p += 2

    for p in range(2, n + 1):
        if prime[p] and k > 0:
            res *= p
            k -= 1
            res %= 1000000007
    return res


n = int(input())
print(Eratosthenes(n))
