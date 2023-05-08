// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1591
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100000;
const int MAX_QUERY = 32000;

bool is_prime[MAX_N + 1];
vector<int> primes;

void Sieve(int n) {
  for (int i = 0; i <= n; i++) is_prime[i] = true;
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i <= n; i++) {
    if (is_prime[i]) {
      for (int j = i * i; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  for (int i = 0; i <= n; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
}

vector<vector<int>> intervals;

void ComputeIntervals(void) {
  int n_primes = (int)primes.size();
  for (int l = 0; l < n_primes - 2; l++) {
    if (primes[l] > MAX_QUERY) break;
    int delta = primes[l + 1] - primes[l];
    int r = l + 2;
    while (r < n_primes && primes[r] - primes[r - 1] == delta) r++;
    r--;
    if (r == l + 1) continue;
    if (primes[r] > MAX_QUERY) break;
    if (l > 0 && primes[l] - primes[l - 1] == delta) continue;
    vector<int> interval;
    for (int i = l; i <= r; i++) interval.push_back(primes[i]);
    intervals.push_back(interval);
  }
}

int FindFirstInterval(int low) {
  int l = 0;
  int r = (int)intervals.size() - 1;
  // FFFF
  if (intervals[r][0] < low) return -1;
  // TTTT
  if (intervals[l][0] >= low) return l;
  // FFTT
  while (r - l > 1) {
    int m = (l + r) / 2;
    if (intervals[m][0] >= low) {
      r = m;
    } else {
      l = m;
    }
  }
  return r;
}

void Solve(int l, int r) {
  int i = FindFirstInterval(l);
  if (i == -1) return;
  int n_intervals = (int)intervals.size();
  while (i < n_intervals && intervals[i].back() <= r) {
    int interval_size = (int)intervals[i].size();
    for (int j = 0; j < interval_size; j++) {
      if (j > 0) cout << " ";
      cout << intervals[i][j];
    }
    cout << endl;
    i++;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  Sieve(MAX_N);
  ComputeIntervals();
  int l, r;
  while (cin >> l >> r) {
    if (l == 0 && r == 0) break;
    Solve(min(l, r), max(l, r));
  }
  return 0;
}