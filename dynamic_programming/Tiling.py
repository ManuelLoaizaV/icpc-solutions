import sys

dp = []
dp.append(1)
dp.append(1)
for i in range (2, 251):
    dp.append(dp[i - 1] + 2 * dp[i - 2])

for n in sys.stdin:
    who = int(n)
    print(dp[who])