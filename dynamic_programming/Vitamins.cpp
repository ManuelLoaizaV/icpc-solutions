//https://codeforces.com/problemset/problem/1042/B
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

typedef long long Long;

const Long INF = 1e14;
const int N = 1e3;

vector<pair<Long, int>> products;

void TurnOn(int& mask, int bit) {
  mask = mask | (1 << bit);
}

Long dp[N][8];
bool is_done[N][8];

Long DP(int i, int mask) {
  if (mask == 7) return 0;
  if (i < 0) return INF;
  if (is_done[i][mask]) return dp[i][mask];
  dp[i][mask] = min(DP(i - 1, mask), products[i].first + DP(i - 1, mask | products[i].second));
  is_done[i][mask] = true;
  return dp[i][mask];
}

int main(void) {
  ios::sync_with_stdio(0);
  cin.tie(nullptr);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    Long value;
    string vitamins;
    cin >> value >> vitamins;
    int mask = 0;
    for (char c : vitamins) {
      int bit = c - 'A';
      TurnOn(mask, bit);
    }
    products.push_back({value, mask});
  }
  if (DP(n - 1, 0) < INF) {
    cout << DP(n - 1, 0) << '\n';
  } else {
    cout << -1 << '\n';
  }
  return 0;
}
