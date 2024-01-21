// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=438
#include <bits/stdc++.h>
#include <string>

#ifndef ONLINE_JUDGE
#define debug(x) cerr << "[" << #x << "]: " << x << endl
#else
#define debug(x) 69
#endif

using namespace std;

typedef long long Long;
typedef long double Double;
typedef pair<Long, Long> Pair;

const int N = 1e6;
const Long MOD = 998244353LL;
const Long INF = 1e18;
const Double PI = acos(-1);
const Double EPS = 1e-9;

const char A = 'a';
const char ZERO = '0';
const char ENDL = '\n';

const string YES = "YES";
const string NO = "NO";

void Solve(void) {
  vector<int> heights;
  string line;
  while (getline(cin, line)) {
    if (line == "") break;
    int height = stoi(line);
    heights.push_back(height);
  }

  int n = (int)heights.size();
  // dp(l): smallest last element for a LIS of length l
  vector<int> dp(n + 1, INT_MAX);
  dp[0] = INT_MIN;

  vector<int> ids(n + 1, -1);
  vector<int> parents(n + 1, -1);
  for (int i = 0; i < n; i++) {
    int len = upper_bound(dp.begin(), dp.end(), heights[i]) - dp.begin();
    if (dp[len - 1] < heights[i]) {
      ids[len] = i;
      parents[i] = ids[len - 1];
      dp[len] = heights[i];
    }
  }

  int lis = INT_MIN;
  for (int i = n; i >= 0; i--) {
    if (dp[i] < INT_MAX) {
      lis = i;
      break;
    }
  }

  cout << "Max hits: " << lis << ENDL;
  stack<int> solution;
  int id = ids[lis];
  while (id != -1) {
    solution.push(id);
    id = parents[id];
  }
  while (!solution.empty()) {
    cout << heights[solution.top()] << ENDL;
    solution.pop();
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string line;
  int T;
  getline(cin, line);
  T = stoi(line);
  getline(cin, line);
  for (int t = 0; t < T; t++) {
    if (t > 0) cout << ENDL;
    Solve();
  }
  return 0;
}
