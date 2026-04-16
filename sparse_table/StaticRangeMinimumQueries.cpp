// https://cses.fi/problemset/task/1647/
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

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int N, Q;
  cin >> N >> Q;
  vector<int> v(N);
  for (auto &e : v)
    cin >> e;
  RMQ<int> table(v);
  while (Q--) {
    int L, R;
    cin >> L >> R;
    cout << table.QueryValue(L - 1, R) << endl;
  }
  return 0;
}