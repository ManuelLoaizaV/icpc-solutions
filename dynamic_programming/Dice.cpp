//https://www.spoj.com/problems/AE2A/
#include <iostream>
using namespace std;

typedef long long Long;
typedef long double Double;

// DP(n, k): Probabilidad de obtener k sumando los resultados de tirar n dados.
// Primer detalle:
// Si k < n o k > 6n, DP(n, k) = 0.
// Segundo detalle:
// Sea n fijo, DP_n(k) con n <= k <= 6n es concavo, alcanzado su maximo en el centro.
// Tercer detalle:
// Sea n1 < n2, max DP_n1 > max DP_n2
// Fusionando estos detalles, analice en un codigo en Python el valor de DP(n, 7 * n / 2)
// obteniendo DP(547, 1914) * 100 < 1.
/*
N = 3001
is_done = [[False for x in range(N)] for y in range(N)]
dp = [[0 for x in range(N)] for y in range(N)]
def f(n, k):
    if k < 0:
        return 0
    if n == 0:
        if k == 0:
            return 1
        return 0
    if k == 0:
        return 0
    if is_done[n][k]:
        return dp[n][k]
    for i in range(1, 7):
        dp[n][k] += f(n - 1, k - i)
    is_done[n][k] = True
    return dp[n][k]

while True:
    n, k = input("Ingrese n, k: ").split(" ")
    n = int(n)
    k = int(k)
    ans = f(n, k) * 100 / (6 ** n)
    print(ans)
*/

const int N = 550;
bool is_done[N + 1][6 * N + 1];
Double dp[N + 1][6 * N + 1];

Double DP(Long n, Long k) {
  if (k < 0) return 0.0;
  if (n == 0) {
    if (k == 0) return 1.0;
    return 0.0;
  }
  if (k == 0) return 0.0;
  if (is_done[n][k]) return dp[n][k];
  for (Long i = 1; i <= 6; i++) dp[n][k] += (DP(n - 1, k - i) / 6);
  is_done[n][k] = true;
  return dp[n][k];
}

void Solve(void) {
  Long n, k;
  cin >> n >> k;
  if (k < n || k > 6 * n) {
    cout << 0 << '\n';
    return;
  }
  if (n >= N) {
    cout << 0 << '\n';
    return;
  }
  Long ans = DP(n, k) * 100;
  cout << ans << '\n';
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
