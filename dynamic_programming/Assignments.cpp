//https://www.spoj.com/problems/ASSIGN/
#include <iostream>
using namespace std;

typedef long long Long;

const int N = 20;
const int MASK = 1 << 20;

int n;
bool likes[N][N];

bool is_done[MASK][N];
Long dp[MASK][N];

Long GetBit(Long mask, Long bit) {
  return (mask >> bit) & 1LL;
}

void TurnOn(Long& mask, Long bit) {
  mask = mask | (1LL << bit);
}

void TurnOff(Long& mask, Long bit) {
  mask = mask & (~(1 << bit));
}

Long DP(Long mask, Long who) {
  if (who == n) return 1;
  if (is_done[mask][who]) return dp[mask][who];
  dp[mask][who] = 0;
  Long aux = mask;
  for (int bit = 0; bit < n; bit++) {
    if (GetBit(mask, bit) == 0 && likes[who][bit]) {
      TurnOn(aux, bit);
      dp[mask][who] += DP(aux, who + 1);
      TurnOff(aux, bit);
    }
  }  
  is_done[mask][who] = true;
  return dp[mask][who];
}

void Solve(void) {
  cin >> n;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> likes[i][j];
  int mx = 1 << n;
  for (int i = 0; i < mx; i++)
    for (int j = 0; j < n; j++)
      is_done[i][j] = false;
  cout << DP(0, 0) << '\n';
}

int main(void) {
  int t;
  cin >> t;
  while (t--) Solve();
  return 0;
}
