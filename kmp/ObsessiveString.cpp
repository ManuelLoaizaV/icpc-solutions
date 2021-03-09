//https://codeforces.com/problemset/problem/494/B
#include <bits/stdc++.h>
using namespace std;

typedef long long Long;

const Long MOD = 1e9 + 7;
const int ALPHABET = 26;

Long Add(Long a, Long b) {
  return (a + b) % MOD;
}

vector<int> CalculatePi(const string& s) {
  int n = s.size();
  vector<int> pi(n, 0);
  for (int i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j]) j = pi[j - 1];
    if (s[i] == s[j]) j++;
    pi[i] = j;
  }
  return pi;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  string s, t;
  cin >> s >> t;
  if (t.size() > s.size()) {
    cout << 0 << '\n';
    return 0;
  }
  int n = (int) s.size();
  int sz = (int) t.size();
  vector<int> pi = CalculatePi(t + '#' + s);
  vector<bool> found(n, false);
  for (int i = sz + 1; i < (int) pi.size(); i++)
    if (pi[i] == sz) found[i - sz - 1] = true;
  vector<Long> dp(n, 0);
  vector<Long> sum_sum_dp(n, 0);
  vector<Long> sum_dp(n, 0);
  for (int i = 0; i < n; i++) {
    if (!found[i]) {
      dp[i] = ((i == 0) ?  0 : dp[i - 1]);
    } else {
      // [0 .. j] [i .. [pos - sz + 1 .. pos]]
      // Como rango solo contribuyo todas las posiciones que mi extremo
      // izquierdo puede llegar a ser conteniendome sin colocar mas rangos
      int left = i - sz + 1;
      dp[i] = left + 1;
      // \sum_{j < left} \sum_{k <= j} dp[k]
      if (left > 0) dp[i] = Add(dp[i], sum_sum_dp[left - 1]);
    }
    sum_dp[i] = ((i == 0) ? 0 : sum_dp[i - 1]);
    sum_dp[i] = Add(sum_dp[i], dp[i]);
    sum_sum_dp[i] = ((i == 0) ? 0 : sum_sum_dp[i - 1]);
    sum_sum_dp[i] = Add(sum_sum_dp[i], sum_dp[i]);
  }
  cout << sum_dp[n - 1] << '\n';
  return 0;
}
