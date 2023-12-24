// https://codeforces.com/contest/1904/problem/D2
#include <algorithm>
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 2e5;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";

// The Fenwick Tree structure functions as an OST/multiset for indexes within the range [0, tree_n).
// Set(index, 1): set.insert(index).
// Update(index, 1): multiset.insert(index).
// Set(index, 0): set.erase(index).
// Update(index, -1): multiset.erase(index).
// Get(index): set.count(index), multiset.count(index).
// Query(index): ost.order_of_key(index).
// FindLastPrefix(k): Find k-th smallest element (0-indexed). Returns tree_n for k >= multiset.size().
template<typename T>
struct FenwickTree {
  int tree_n = 0;
  T tree_sum = T();
  vector<T> tree;
  FenwickTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    tree_n = n;
    tree.assign(tree_n + 1, T());
  }
  // Initialization in O(n)
  template<typename T_array>
  void Build(const T_array& initial) {
    assert(int(initial.size()) == tree_n);
    tree_sum = T();
    for (int i = 1; i <= tree_n; i++) {
      tree[i] = initial[i - 1];
      tree_sum += initial[i - 1];
      for (int k = (i & -i) >> 1; k > 0; k >>= 1)
        tree[i] += tree[i - k];
    }
  }
  // Adds change to a[index]
  void Update(int index, const T& change) {
    assert(0 <= index && index < tree_n);
    tree_sum += change;
    for (int i = index + 1; i <= tree_n; i += (i & -i))
      tree[i] += change;
  }
  // Returns the sum of the range [0, end)
  T Query(int end) const {
    end = min(end, tree_n);
    T sum = T();
    while (end > 0) {
      sum += tree[end];
      end -= (end & -end);
    }
    return sum;
  }
  // Returns the sum of the range [start, tree_n)
  T QuerySuffix(int start) const {
    return tree_sum - Query(start);
  }
  // Returns the sum of the range [start, end)
  T Query(int start, int end) const {
    return Query(end) - Query(start);
  }
  // Returns a[index] in O(1) amortized across every index
  T Get(int index) const {
    assert(0 <= index && index < tree_n);
    int above = index + 1;
    T sum = tree[above];
    above -= (above & -above);
    while (index != above) {
      sum -= tree[index];
      index -= (index & -index);
    }
    return sum;
  }
  bool Set(int index, T value) {
    assert(0 <= index && index < tree_n);
    T current = Get(index);
    if (current == value) return false;
    Update(index, value - current);
    return true;
  }
  static int HighestBit(unsigned x) {
    if (x == 0) return -1;
    return 31  - __builtin_clz(x);
  }
  // Returns largest prefix in [0, tree_n] such that Query(prefix) <= sum.
  // Returns -1 if no such prefix exists (sum < 0).
  int FindLastPrefix(T sum) const {
    if (sum < T()) return -1;
    int prefix = 0;
    for (int k = HighestBit(tree_n); k >= 0; k--) {
      int nxt = prefix + (1 << k);
      if (nxt <= tree_n && tree[nxt] <= sum) {
        prefix = nxt;
        sum -= tree[prefix];
      }
    }
    return prefix;
  }
};

struct Search {
  vector<int> original, reversed;
  void Push(int index) { original.push_back(index); }
  void Build(void) {
    for (int index : original) reversed.push_back(-index);
    reverse(reversed.begin(), reversed.end());
  }
  int FirstGT(int index) {
    auto it = upper_bound(original.begin(), original.end(), index);
    if (it == original.end()) return -1;
    return *it;
  }
  int FirstGE(int index) {
    auto it = lower_bound(original.begin(), original.end(), index);
    if (it == original.end()) return -1;
    return *it;
  }
  int LastLT(int index) {
    auto it = upper_bound(reversed.begin(), reversed.end(), -index);
    if (it == reversed.end()) return -1;
    return -*it;
  }
  int LastLE(int index) {
    auto it = lower_bound(reversed.begin(), reversed.end(), -index);
    if (it == reversed.end()) return -1;
    return -*it;
  }
};

void Solve(void) {
  int n;
  cin >> n;
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    a[i]--;
  }
  for (int i = 0; i < n; i++) {
    cin >> b[i];
    b[i]--;
  }

  vector<Search> indexes(n);
  for (int i = 0; i < n; i++) {
    indexes[a[i]].Push(i);
  }
  for (int i = 0; i < n; i++) {
    indexes[i].Build();
  }

  vector<vector<int>> target_indexes(n);
  for (int i = 0; i < n; i++) {
    target_indexes[b[i]].push_back(i);
  }

  FenwickTree<int> below(n), above(n);
  for (int i = 0; i < n; i++) above.Set(i, 1);
  bool possible = true;
  for (int target_value = 0; target_value < n; target_value++) {
    for (int original_index : indexes[target_value].original) {
      above.Set(original_index, 0);
    }
    for (int target_index : target_indexes[target_value]) {
      int last_le = indexes[target_value].LastLE(target_index);
      int first_ge = indexes[target_value].FirstGE(target_index);
      if (
        last_le == target_index ||
        last_le != -1 && below.Query(last_le, target_index + 1) == 0 && above.Query(last_le, target_index + 1) == 0 ||
        first_ge != -1 && below.Query(target_index, first_ge + 1) == 0 && above.Query(target_index, first_ge + 1) == 0
      ) {
        continue;
      }
      possible = false;
      break;
    }
    if (!possible) break;
    for (int target_index: target_indexes[target_value]) {
      below.Set(target_index, 1);
    }
  }

  if (possible) {
    cout << YES << ENDL;
  } else {
    cout << NO << ENDL;
  }
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  for (int t = 0; t < T; t++) Solve();
  return 0;
}
