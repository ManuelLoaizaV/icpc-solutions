// https://atcoder.jp/contests/abc036/tasks/abc036_c
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

typedef long long Long;
typedef long double Double;

// Discretizes a fixed set of values into IDs in [0, U)
// preserving their order but not distances.
template<typename T>
struct Discretizer {
  vector<T> values;  // Sorted unique input values.
  vector<int> ids;  // IDs of the input values.

  // Builds the sorted unique value vector and assigns an ID to each input value.
  // Time complexity: O(n lg n).
  Discretizer(const vector<T>& input) {
    values = input;
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
    ids.resize(input.size());
    for (int i = 0; i < input.size(); i++) {
      ids[i] = lower_bound(values.begin(), values.end(), input[i]) - values.begin();
    }
  }

  // Returns the ID assigned to input position i.
  // Time complexity: O(1).
  int At(size_t i) const {
    return ids.at(i);
  }

  // Returns the ID of value, or -1 if value was not in the input.
  // Time complexity: O(lg U).
  int GetId(const T& value) const {
    auto it = lower_bound(values.begin(), values.end(), value);
    if (it == values.end() || *it != value) return -1;
    return it - values.begin();
  }

  // Returns the original value for id.
  // Requires id in [0, U).
  // Time complexity: O(1).
  const T& GetValue(int id) const {
    return values.at(id);
  }

  // Returns the number of distinct values U.
  // Time complexity: O(1).
  int Size(void) const {
    return (int)values.size();
  }
};

void Solve(void) {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& e : a) cin >> e;
    Discretizer d(a);
    for (int i = 0; i < n; i++) {
        cout << d.At(i) << endl;
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    while (t--) Solve();
    return 0;
}