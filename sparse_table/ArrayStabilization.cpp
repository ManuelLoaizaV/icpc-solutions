// https://codeforces.com/problemset/problem/1547/F
#include <bits/stdc++.h>
using namespace std;

// Range minimum/maximum query using a sparse table.
// Set minimum_mode to true for min queries, false for max queries.
template <typename T> struct SparseTable {
  int N;
  vector<vector<T>> table;
  SparseTable(const vector<T> &_values = {}) {
    if (!_values.empty())
      Compute(_values);
  }

  // Compute the sparse table. Time complexity: O(N lg N).
  void Compute(const vector<T> &_values) {
    N = (int)_values.size();
    int levels = HighestBit(N) + 1;
    table.resize(levels);
    for (int level = 0; level < levels; level++)
      table[level].resize(N - (1 << level) + 1);
    for (int i = 0; i < N; i++)
      table[0][i] = _values[i];
    for (int level = 1; level < levels; level++)
      for (int i = 0; i <= N - (1 << level); i++)
        table[level][i] = Merge(table[level - 1][i],
                                table[level - 1][i + (1 << (level - 1))]);
  }

  T Merge(T a, T b) { return std::gcd(a, b); }

  // Returns floor(lg n), which is the index of the highest set bit.
  // Returns -1 if n is zero.
  static int HighestBit(unsigned n) { return std::bit_width(n) - 1; }

  // Returns the minimum/maximum value in the range [L, R).
  // Time complexity: O(1).
  T Query(int L, int R) {
    assert(0 <= L && L < R && R <= N);
    int level = HighestBit(R - L);
    return Merge(table[level][L], table[level][R - (1 << level)]);
  }
};

bool Check(int steps, int N, SparseTable<int>& sparse_table) {
    int target = sparse_table.Query(0, std::min(steps + 1, 2 * N));
    for (int i = 1; i < N; i++) {
        int value = sparse_table.Query(i, std::min(2 * N, i + steps + 1));
        if (value != target) return false;
    }
    return true;
}

void Solve(void) {
  int N;
  cin >> N;
  vector<int> a(2 * N);
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    a[i + N] = a[i];
  }
  SparseTable<int> sparse_table(a);

  if (Check(0, N, sparse_table)) {
    cout << 0 << endl;
    return;
  }
  int low = 0;
  int high = N;
  while (high - low > 1) {
    int mid = (low + high) / 2;
    if (Check(mid, N, sparse_table)) {
        high = mid;
    } else {
        low = mid;
    }
  }
  cout << high << endl;
}

int main(void) {
  {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    while (T--)
      Solve();
    return 0;
  }
}