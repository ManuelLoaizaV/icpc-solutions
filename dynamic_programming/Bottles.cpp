//https://codeforces.com/problemset/problem/730/J
//#pragma GCC optimize ("Ofast,unroll-loops")
//#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#include <unistd.h>
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

typedef long long Long;
typedef long double Double;
typedef unsigned long long ULong;
typedef pair<Long, Long> Pair;

const int N = 1e2;
const int INF = 1e6;
const Double EPS = 1e-9;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
Long random(Long a, Long b) { return uniform_int_distribution<Long> (a, b) (rng); }

vector<int> used, vol;
int total_sum;
int dp[N][N + 1][N * N + 1];
bool done[N][N + 1][N * N + 1];

// DP(i, j, k): Maxima cantidad de litros que pertenecen a las botellas que
// seleccionemos en las posiciones [pos .. n - 1] cuando tenemos por seleccionar
// j botellas y hemos acumulado k litros.

int DP(int pos, int rem, int sum) {
  if (rem == 0) {
    if (sum >= total_sum) return 0;
    return -INF;
  }
  if (pos == (int) used.size()) return -INF;
  if (done[pos][rem][sum]) return dp[pos][rem][sum];
  dp[pos][rem][sum] = DP(pos + 1, rem, sum);
  dp[pos][rem][sum] = max(dp[pos][rem][sum], used[pos] + DP(pos + 1, rem - 1, sum + vol[pos]));
  done[pos][rem][sum] = true;
  return dp[pos][rem][sum];
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n;
  cin >> n;
  used = vector<int>(n);
  vol = vector<int>(n);
  total_sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> used[i];
    total_sum += used[i];
  }
  for (int i = 0; i < n; i++) cin >> vol[i];
  
  // Hallo la menor cantidad de botellas que necesito
  vector<int> aux = vol;
  sort(aux.begin(), aux.end());
  int mn = 0;
  int current = 0;
  for (int i = n - 1; i >= 0; i--) {
    current += aux[i];
    mn++;
    if (current >= total_sum) break;
  }
  cout << mn << " " << total_sum - DP(0, mn, 0) << '\n';
  return 0;
}

