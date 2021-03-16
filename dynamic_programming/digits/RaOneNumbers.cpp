//https://www.spoj.com/problems/RAONE/
#include <bits/stdc++.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int N = 9;
const int S = 75;

int dp[N][2][S][S];
bool done[N][2][S][S];
deque<int> s;

int DP(int pos, bool lower, int even, int odd) {
  if (pos == (int) s.size()) {
    return (odd - even == 1) ? 1 : 0;
  }
  if (done[pos][lower][even][odd]) return dp[pos][lower][even][odd];
  dp[pos][lower][even][odd] = 0;
  int limit = (lower) ? 9 : s[pos];
  for (int d = 0; d <= limit; d++) {
    if (pos & 1) {
      dp[pos][lower][even][odd] += DP(pos + 1, lower || d < limit, even, odd + d); 
    } else {
      dp[pos][lower][even][odd] += DP(pos + 1, lower || d < limit, even + d, odd);
    }
  }
  done[pos][lower][even][odd] = true;
  return dp[pos][lower][even][odd];
}

int Solve(int n) {
  if (n <= 0) return 0LL;
  // Construir el numero en el deque
  s.clear();
  for (int i = 0; i < N; i++) {
    s.push_front(n % 10);
    n /= 10;
  }
  // Limpiar el dp y calcular el valor
  for (int i = 0; i < N; i++)
    for (int j = 0; j < 2; j++)
        for (int odd = 0; odd < S; odd++)
          for (int even = 0; even < S; even++)
            done[i][j][even][odd] = false;
  return DP(0, false, 0, 0);
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int l, r;
    cin >> l >> r;
    int ans = Solve(r) - Solve(l - 1);
    cout << ans << '\n';
  }
  return 0;
}
