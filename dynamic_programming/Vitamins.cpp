#include <bits/stdc++.h>
#define FAST_IO ios::sync_with_stdio(0);cin.tie(NULL)
using namespace std;

const int INF = 1e9;
const int N = 1e3;

typedef long long Long;

struct Juice {
  Long price;
  bool has_vitamin[3];
};

vector<Juice> juices;
int n;
Long dp[N][2][2][2];
bool is_done[N][2][2][2];

Long DP(int pos, bool has_a, bool has_b, bool has_c) {
  if (pos == n) {
    if (has_a && has_b && has_c) return 0;
    return INF;
  }
  Long& memo = dp[pos][has_a][has_b][has_c];
  if (is_done[pos][has_a][has_b][has_c]) return memo;
  memo = min(DP(pos + 1, has_a, has_b, has_c), juices[pos].price + DP(pos + 1,
        has_a | juices[pos].has_vitamin[0],
        has_b | juices[pos].has_vitamin[1],
        has_c | juices[pos].has_vitamin[2]));
  is_done[pos][has_a][has_b][has_c] = true;
  return memo;
}

int main(void) {
  FAST_IO;
  cin >> n;
  juices.resize(n);
  for (int i = 0; i < n; i++) {
    cin >> juices[i].price;
    string s;
    cin >> s;
    for (int j = 0; j < 3; j++) juices[i].has_vitamin[j] = false;
    for (char c : s) juices[i].has_vitamin[c - 'A'] = true;
  }
  Long ans = DP(0, 0, 0, 0);
  if (ans >= INF) {
    cout << -1 << '\n';
  } else {
    cout << ans << '\n';
  }
  return 0;
}
