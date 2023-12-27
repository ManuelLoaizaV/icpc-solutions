// https://codeforces.com/contest/1917/problem/D
#include <bits/stdc++.h>

#define debug(x) cout << #x << " = " << x << endl

using namespace std;

typedef long long Long;

const int N = 1e6;
const Long INF = 1e18;
const char ENDL = '\n';
const string YES = "YES";
const string NO = "NO";
const Long MOD = 998244353LL;
const Long LG = 20;

struct Mint {
  Long v; // Holds the value of the modular integer
  explicit operator Long() const { return v; }
  // Constructors
  Mint() { v = 0; }
  Mint(Long _v) {
    // Modulo operation to keep value in range [-MOD, MOD)
    v = (-MOD < _v && _v < MOD) ? _v : _v % MOD;
    if (v < 0) v += MOD; // Ensure non-negative value
  }
  // Comparison operators
  friend bool operator==(const Mint &a, const Mint &b) { return a.v == b.v; }
  friend bool operator!=(const Mint &a, const Mint &b) { return !(a == b); }
  friend bool operator<(const Mint &a, const Mint &b) { return a.v < b.v; }
  // Arithmetic operators
  Mint &operator+=(const Mint &m) {
    if ((v += m.v) >= MOD) v -= MOD;
    return *this;
  }
  Mint &operator-=(const Mint &m) {
    if ((v -= m.v) < 0) v += MOD;
    return *this;
  }
  Mint &operator*=(const Mint &m) {
    v = v * m.v % MOD;
    return *this;
  }
  Mint &operator/=(const Mint &m) { return (*this) *= inv(m); }
  // Utility functions
  friend Mint pow(Mint a, Long p) {
    Mint ans = 1;
    assert(p >= 0);
    for (; p; p /= 2, a *= a) if (p & 1) ans *= a;
    return ans;
  }
  friend Mint inv(const Mint &a) {
    assert(a.v != 0);
    return pow(a, MOD - 2);
  }
  Mint operator-() const { return Mint(-v); }
  Mint &operator++() { return *this += 1; }
  Mint &operator--() { return *this -= 1; }
  Mint operator++(int) {
    v++;
    if (v == MOD) v = 0;
    return Mint(v);
  }
  Mint operator--(int) {
    v--;
    if (v < 0) v = MOD - 1;
    return Mint(v);
  }
  // Binary arithmetic operators
  friend Mint operator+(Mint a, const Mint &b) { return a += b; }
  friend Mint operator-(Mint a, const Mint &b) { return a -= b; }
  friend Mint operator*(Mint a, const Mint &b) { return a *= b; }
  friend Mint operator/(Mint a, const Mint &b) { return a /= b; }
  // Stream insertion and extraction operators
  friend ostream &operator<<(ostream &os, const Mint &m) {
    os << m.v;
    return os;
  }
  friend istream &operator>>(istream &is, Mint &m) {
    Long x;
    is >> x;
    m.v = x;
    return is;
  }
};

// Fenwick Tree structure works as an OST/multiset for indexes within the range [0, tree_n).
// Set(index, 1): set.insert(index).
// Update(index, 1): multiset.insert(index).
// Set(index, 0): set.erase(index).
// Update(index, -1): multiset.erase(index).
// Get(index): set.count(index), multiset.count(index).
// Query(index): ost.order_of_key(index).
// FindLastPrefix(k): Find k-th smallest element (0-indexed). Returns tree_n for k >= multiset.size().
template<typename T>
struct FenwickTree {
  Long tree_n = 0;
  T tree_sum = T();
  vector<T> tree;
  FenwickTree(int n = -1) { if (n >= 0) Init(n); }
  void Init(int n) {
    tree_n = n;
    tree.assign(tree_n + 1, T());
  }
  // Initialization in O(n)
  template<typename A>
  void Build(const A& initial) {
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
  T Query(Long end) const {
    end = min(end, tree_n);
    T sum = T();
    while (end > 0) {
      sum += tree[end];
      end -= (end & -end);
    }
    return sum;
  }
  // Returns the sum of the range [start, tree_n)
  T QuerySuffix(Long start) const {
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
    return 31 - __builtin_clz(x);
  }
  // Returns largest prefix in [0, tree_n] such that Query(prefix) <= sum.
  // Returns -1 if no such prefix exists (sum < 0).
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

void Solve(void) {
  Long n, k;
  cin >> n >> k;
  vector<int> p(n);
  for (int i = 0; i < n; i++) cin >> p[i];
  vector<int> q(k);
  for (int i = 0; i < k; i++) cin >> q[i];

  Mint n_q_inversions = 0;
  FenwickTree<int> q_ft(k);
  for (int i = 0; i < k; i++) {
    n_q_inversions += q_ft.QuerySuffix(q[i]);
    q_ft.Set(q[i], 1);
  }

  FenwickTree<int> ft(2 * n);
  Mint n_inversions = 0;
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      Long lg = min(LG, k);
      vector<Long> cnt(lg, 0);
      Long factor = 1LL;
      for (int j = 0; j < lg; j++) {
        cnt[j] = ft.Query(p[i] / factor + 1LL);
        factor *= 2LL;
      }
      for (Long j = 0; j < lg - 1; j++) {
        n_inversions += (cnt[j] - cnt[j + 1]) * (k - j) * (k - j - 1LL) / 2LL;
      }
      n_inversions += cnt[lg - 1] * (k - lg - 1LL) * (k - lg) / 2LL;

      factor = 1LL;
      for (int j = 0; j < lg; j++) {
        cnt[j] = ft.QuerySuffix(factor * p[i]);
        factor *= 2LL;
      }
      for (Long j = 0; j < lg - 1; j++) {
        n_inversions += (cnt[j] - cnt[j + 1]) * (k * j + k * (k + 1LL) / 2LL - j * (j + 1LL) / 2LL);
      }
      n_inversions += cnt[lg - 1] * (k * (lg - 1LL) + k * (k + 1LL) / 2LL - lg * (lg - 1LL) / 2LL);
    }
    ft.Set(p[i], 1);
    n_inversions += n_q_inversions;
  }
  cout << n_inversions << ENDL;
}

int main(void) {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--) Solve();
  return 0;
}

