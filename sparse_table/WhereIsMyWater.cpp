// https://codeforces.com/contest/2207/problem/C
#include <bits/stdc++.h>
using namespace std;

// Range minimum/maximum query using a sparse table.
// Set minimum_mode to true for min queries, false for max queries.
template <typename T, bool minimum_mode = true> struct RMQ {
  int N;
  vector<T> values;
  vector<vector<T>> table;
  RMQ(const vector<T> &_values = {}) {
    if (!_values.empty())
      Compute(_values);
  }

  // Compute the sparse table. Time complexity: O(N lg N).
  void Compute(const vector<T> &_values) {
    N = (int)_values.size();
    values = _values;
    int levels = HighestBit(N) + 1;
    table.resize(levels);
    for (int level = 0; level < levels; level++)
      table[level].resize(N - (1 << level) + 1);
    for (int i = 0; i < N; i++)
      table[0][i] = i;
    for (int level = 1; level < levels; level++)
      for (int i = 0; i <= N - (1 << level); i++)
        table[level][i] = BetterIndex(table[level - 1][i],
                                      table[level - 1][i + (1 << (level - 1))]);
  }

  // Returns floor(lg(n)), which is the index of the highest set bit.
  // Returns -1 if n is zero.
  static int HighestBit(unsigned n) { return std::bit_width(n) - 1; }

  // Compares two indices and returns the one pointing to the better value.
  // In case of a tie, the rightmost index is returned.
  int BetterIndex(int L, int R) const {
    if (minimum_mode)
      return values[L] < values[R] ? L : R;
    return values[L] > values[R] ? L : R;
  }

  // Returns the index of the optimal value in the range [L, R).
  int QueryIndex(int L, int R) const {
    assert(0 <= L && L < R && R <= N);
    int level = HighestBit(R - L);
    return BetterIndex(table[level][L], table[level][R - (1 << level)]);
  }

  // Returns the minimum/maximum value in the range [L, R).
  // Time complexity: O(1).
  T QueryValue(int L, int R) const { return values[QueryIndex(L, R)]; }
};

void Solve(void) {
  int64_t n, h;
  cin >> n >> h;
  vector<int64_t> a(n);
  for (auto &e : a)
    cin >> e;
  RMQ<int64_t, false> table(a);
  int64_t best{0LL};
  vector<int64_t> water(n, 0LL);
  for (int i = 0; i < n; i++) {
    int64_t max_height{a[i]};
    for (int j = i; j < n; j++) {
      max_height = std::max(max_height, a[j]);
      water[i] += h - max_height;
    }
    max_height = a[i];
    for (int j = i - 1; j >= 0; j--) {
      max_height = std::max(max_height, a[j]);
      water[i] += h - max_height;
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      int k = table.QueryIndex(i, j + 1);
      int64_t value = water[i] + water[j] - water[k];
      best = std::max(best, value);
    }
  }
  cout << best << endl;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    Solve();
  return 0;
}