input_file = open("jealous.in", "r")
a, b, p, q = [int(i) for i in input_file.readline().split(" ")]
#print(a, b, p, q)

def Log(n, m):
    exp = 0
    pot = 1
    while pot * m <= n:
        pot *= m
        exp += 1
    return exp

def InRange(n, i, j):
    return n // ((p ** i) * (q ** j))

def Count(n):
    if n == 0:
        return 0
    max_p = Log(n, p)
    max_q = Log(n, q)
    cnt = 0
    for i in range(1, max_p + 1):
        for j in range(0, min(i - 1, max_q) + 1):
            cnt += (InRange(n, i, j) - InRange(n, i + 1, j) - InRange(n, i, j + 1) + InRange(n, i + 1, j + 1))
    return cnt

ans = Count(b) - Count(a - 1)
output_file = open("jealous.out", "w")
output_file.write(str(ans))
#print(ans)

input_file.close()
output_file.close()
