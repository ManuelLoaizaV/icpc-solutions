// https://cses.fi/problemset/task/1648/
#include <bits/stdc++.h>
#include <cassert>
using namespace std;

typedef long long Long;
typedef long double Double;

// Fenwick Tree for point-update-range-sum queries over 0-indexed range [0, tree_n).
// Requires (T, +, T()) to be an abelian group because Query and Update combines segments in arbitrary order.
//
// With nonnegative values, this tree can represent a Red-Black Tree over [0, tree_n).
//
// Set over [0, tree_n):
//  insert(x): Set(x, 1)
//  erase(x): Set(x, 0)
//  count(x): Get(x)
//
// Multiset over [0, tree_n):
//  insert(x): Update(x, 1)
//  erase(x): Update(x, -1) if Get(x) > 0
//  count(x): Get(x)
//
// Order Statistics tree:
//  order_of_key(k): Query(k) returns the count of elements < k.
//  find_by_order(k): FindLastPrefix(k) returns k-th smallest element (0-indexed).
//                    Returns tree_n if k >= ost.size().
template<typename T>
struct FenwickTree {
  int tree_n = 0;
  T tree_sum = T();
  vector<T> tree;
  // Creates a tree to represent n identity elements.
  // Time complexity: O(n)
  FenwickTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    tree_n = n;
    tree_sum = T();
    tree.assign(tree_n + 1, T());
  }

  // Builds the tree from a.
  // Time complexity: O(n).
  template<typename A>
  void Build(const A& a) {
    assert(int(a.size()) == tree_n);
    tree_sum = T();
    for (int i = 1; i <= tree_n; i++) {
      tree[i] = a[i - 1];
      tree_sum += a[i - 1];
      for (int k = (i & -i) >> 1; k > 0; k >>= 1)
        tree[i] += tree[i - k];
    }
  }

  // Adds change to a[index].
  // Time complexity: O(lg n).
  void Update(int index, const T& change) {
    assert(0 <= index && index < tree_n);
    tree_sum += change;
    for (int i = index + 1; i <= tree_n; i += (i & -i))
      tree[i] += change;
  }

  // Returns the sum of a[0..end).
  // Values of end greater than tree_n are clamped.
  // Time complexity: O(lg n).
  T Query(int end) const {
    end = min(end, tree_n);
    T sum = T();
    while (end > 0) {
      sum += tree[end];
      end -= (end & -end);
    }
    return sum;
  }

  // Returns the sum of a[start..tree_n).
  // Time complexity: O(lg n).
  T QuerySuffix(int start) const {
    return tree_sum - Query(start);
  }

  // Returns the sum of a[start..end).
  // Requires 0 <= start <= end.
  // Time complexity: O(lg n).
  T Query(int start, int end) const {
    return Query(end) - Query(start);
  }

  // Returns a[index].
  // Time complexity: O(lg n).
  // Calling Get(i) for every i in [0, tree_n) takes O(n) total time.
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

  // Sets a[index] to value.
  // Returns true if the value changed, false otherwise.
  // Time complexity: O(lg n).
  bool Set(int index, T value) {
    assert(0 <= index && index < tree_n);
    T current = Get(index);
    if (current == value) return false;
    Update(index, value - current);
    return true;
  }

  // Returns floor(lg n) which is the index of the highest set bit or -1 if n is
  // zero. Since C++20, we can use std::bit_width from <bit> header. Fallback
  // for older compilers: 31 - __builtin_clz(n).
  static int HighestBit(unsigned n) {
    if (n == 0) return -1;
    return std::bit_width(n) - 1;
  }

  // Returns the largest prefix length p in [0, tree_n] such that Query(p) <= sum.
  // Returns -1 if no such prefix exists (sum < 0).
  // Returns tree_n if sum >= tree_sum.
  // Time complexity: O(lg n).
  int FindLastPrefix(T sum) const {
    if (sum < T()) return -1;
    int prefix = 0;
    for (int k = HighestBit(tree_n); k >= 0; k--) {
      int nxt = prefix + (1 << k);
      if (nxt <= tree_n && tree[nxt] <= sum) {
        sum -= tree[nxt];
        prefix = nxt;
      }
    }
    return prefix;
  }
};

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, q;
    cin >> n >> q;

    vector<Long> x(n);
    for (auto& e : x) cin >> e;
    FenwickTree<Long> ft(n);
    ft.Build(x);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int k;
            Long u;
            cin >> k >> u;
            ft.Set(k - 1, u);
        } else {
            Long a, b;
            cin >> a >> b;
            cout << ft.Query(a - 1, b) << endl;
        }
    }
    return 0;
}