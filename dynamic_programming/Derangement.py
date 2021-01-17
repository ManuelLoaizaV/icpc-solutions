is_done = []
dp = []
fact = []

def DP(n):
    if n == 1:
        return 0
    if n == 2:
        return 1
    if is_done[n]:
        return dp[n]
    dp[n] = (n - 1) * (DP(n - 2) + DP(n - 1))
    is_done[n] = True
    return dp[n]

n = 20

fact.append(1)
for i in range(1, n + 1):
    fact.append(fact[i - 1] * i)

for i in range(0, n + 1):
    is_done.append(False)
    dp.append(0)

dp[1] = 0
dp[2] = 1
for i in range(1, n + 1):
    favorables = DP(i)
    totales = fact[i]
    p = favorables / totales
    print("i:", i, " p:", p)
