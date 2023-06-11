#https://atcoder.jp/contests/abc192/tasks/abc192_d
def Check(x, b, m):
    ans = 0
    pot = 1
    aux = x
    while aux > 0:
        if pot > m:
            return False
        d = aux % 10
        ans = ans + d * pot
        if ans > m:
            return False
        aux = aux // 10
        pot = pot * b
    return ans <= m

def GetMax(x):
    aux = x
    ans = 0
    while aux > 0:
        d = aux % 10
        ans = max(ans, d)
        aux = aux // 10
    return ans

x = int(input())
m = int(input())

d = GetMax(x)
l = d + 1
r = (10 ** 18) + 5

if not Check(x, l, m):
    print(0)
else:
    if x < 10:
        if x <= m:
            print(1)
        else:
            print(0)
        exit()
    while r - l > 1:
        mid = (l + r) // 2
        if Check(x, mid, m):
            l = mid
        else:
            r = mid
    ans = l - d
    print(ans)
